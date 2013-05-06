/* Make a database the stores <pronunciation>|<pronunciation> pairs */

#include <kcpolydb.h>
#include <cstring>
#include <strops.h>
#include <string>
#include <vector> 

using namespace std;
using namespace kyotocabinet;

int
main (int argc, char **argv)
{
  string s;

  if (argc != 2) {
    cerr << "Arguments are " << argv[0] << " and path to pronunciation dictionary."
      << endl;
    return 1;
  }

  // define a vistor that will put the matching pronunciation in the pron string
  class VisitorPron : public DB::Visitor {
    string val; // the resulting pronunciation
    // Call back when the pronunciation exists
    const char* visit_full(const char* kbuf, size_t ksiz,
                           const char* vbuf, size_t vsiz, size_t *sp) {
      val = string(vbuf, vsiz); // Put the pronunciation in the val
      return NOP;
    }
    // Call back when it doesn't
    const char* visit_empty(const char* kbuf, size_t ksiz, size_t *sp) {
      val = string("*");
      return NOP; // The val string is just "*" meaning no pronunciation found
    }
    public:
    string& get_val() {
      return val;
    }
  };

  // create db obj for pron
  PolyDB cmudb;
  // create the db for the pronunciation/pronun pairs
  PolyDB prondb;

  // Open the dbs
  if (!cmudb.open("../cmudict/cmudict.0.7a.kch")) {
    cerr << "open error: " << cmudb.error().name() << endl;
  }

  if (!prondb.open(argv[1])) {
    cerr << "open error: " << prondb.error().name() << endl;
  }

  while (get_next_sentence(s, stdin) > 0) {

    // print the sentence
    printf("%s\n",s.c_str());

    // remove punctuation (except ')
    replace_unpron_punct(s,' ');

    // remove extra whitespace
    normalize_ws(s);

    // remove punctuation at beginning and end
    remove_begin_end_punct(s);

    // make all uppercase
    str_to_upper(s);

    // print the fixed up sentence
    printf("%s\n",s.c_str());

    // split the sentence into words
    vector<string> words;
    strsplit(s, ' ', &words);

    // make a pronunciation string
    string pronunciation;
    pronunciation.append("| ");

    // flag concerning pronouncability of pronunciation
    int pronouncable = 1;

    for (vector<string>::iterator it = words.begin();
         it != words.end(); ++it) {

      // look up pronunciation of word
      VisitorPron visitor;
      if (!cmudb.accept(it->c_str(), it->length(), &visitor, false)) {
        cerr << "iterate error: " << cmudb.error().name() << endl;
      }

      // if pronunciation is "*" it means this sentence is not pronouncable
      if (visitor.get_val() == string("*")) {
        pronouncable = 0;
        break;
      }
      pronunciation.append(visitor.get_val());
      pronunciation.append(" | ");

      printf("%s ",visitor.get_val().c_str()); // print the pronunciation
      printf("| ");
    }

    normalize_ws(pronunciation);
    
    if (pronouncable) {
      // store the pronunciation and pronunciation
      prondb.set(s.c_str(), pronunciation.c_str());
    }

    printf("\n******************\n\n");
    s.clear();

    fflush(stdout);
  }

  return 0;

}
