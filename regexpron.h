#ifndef REGEXPRON_H
#define REGEXPRON_H 
#include <regex.h>
#include <vector>
#include <string>
#include <kcpolydb.h>
#include <pronops.h>
#include <strops.h> 

using namespace kyotocabinet;

namespace regexpron {


  /* The class that contains the regular expression to test the pronunciation of
   * a dictionary entry against */
  class RegexpronVisitor : public DB::Visitor {

    regex_t re; // The regular expression
    std::vector<std::string> matches; // The strings that match the pronunciation description

    // Call back when the sentence exists
    const char* visit_full(const char* kbuf, size_t ksiz,
                           const char* vbuf, size_t vsiz, size_t *sp)
    {
      // convert the pronunciation to the regex form
      pronops::PronopsOperator pops; // has methods to convert from cmu pronunciation to regex
      std::string vstr(vbuf,vsiz); // make a string object from the pronunciation at this record
      strops::remove_numbers(vstr); // remove numbers
      std::string vre; // the regular expression version of the pronunciation string
      std::string nosep(""); // the non-separator to use when assembling the regex
      std::vector<std::string> words = strops::separate_strings( vstr, ' ' );
      std::vector<std::string> phons = pops.pron_only_phonemes( words );
      std::vector<std::string> rewords = pops.pron_to_regex( phons );
      vre = strops::combine_strings( rewords , nosep );
      if (regexec(&re, vre.c_str(), 0, NULL, 0) == 0) {
        matches.push_back(std::string(kbuf, ksiz)); // store the real sentence (the key)
      }
      return NOP;
    }

    // Callback when the sentence doesn't exist. This is not really used for our
    // purposes but is required.
    const char* visit_empty(const char* kbuf, size_t ksiz, size_t *sp)
    {
      return NOP; // Don't do anything
    }

    public:

    // Construtor, compiles a regular expression from the given string
    RegexpronVisitor(std::string& ex)
    {
      int err;
      /* prepare the regex structure a la libc */
      if ((err = regcomp(&re, ex.c_str(), REG_NOSUB | REG_EXTENDED)))
        std::cerr << "Error " << err << " compiling regular expression "
          << ex << std::endl;
    }

    // Destructor
    ~RegexpronVisitor()
    {
      regfree(&re); // free data allocated during compile
    }

    // Get a reference of the vector of strings that were found to match
    std::vector<std::string>& get_matches()
    {
      return matches;
    }

  }; // RegexpronVisitor

  /* Use the regular expression (re) to search for expressions in the database
   * (db) that match the pronunciation given in the re. */
  static std::vector<std::string> find_strings_with_pron(kyotocabinet::PolyDB& db,
      std::string& re)
  {
    RegexpronVisitor rv(re);
    if (!db.iterate(&rv, false)) {
      std::cerr << "DB iterate error: " << db.error().name() << std::endl;
    }
    return rv.get_matches();
  }

} /* end of regexpron namespace */


#endif /* REGEXPRON_H */
