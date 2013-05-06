#ifndef PRONOPS_H
#define PRONOPS_H 

#include <strops.h>
#include <kcutil.h>
#include <string>
#include <vector>
#include <iostream> 

namespace pronops {

/* A class holding list of vowels. Should not be instantiated directly, but
 * rather is used as a static member of PronopsOperator */
class PronopsStaticData {

  std::vector<std::string> vowels;
  std::vector<std::string> consonances;
  std::vector<std::string> phonemes;
  std::map<std::string,std::string> pronmap;

  public:

  PronopsStaticData()
  {
    vowels.push_back(std::string("AA"));
    vowels.push_back(std::string("AE"));
    vowels.push_back(std::string("AH"));
    vowels.push_back(std::string("AO"));
    vowels.push_back(std::string("AW"));
    vowels.push_back(std::string("AY"));
    vowels.push_back(std::string("EH"));
    vowels.push_back(std::string("ER"));
    vowels.push_back(std::string("EY"));
    vowels.push_back(std::string("IH"));
    vowels.push_back(std::string("IY"));
    vowels.push_back(std::string("OW"));
    vowels.push_back(std::string("OY"));
    vowels.push_back(std::string("UH"));
    vowels.push_back(std::string("UW"));

    consonances.push_back(std::string("B"));
    consonances.push_back(std::string("CH"));
    consonances.push_back(std::string("D"));
    consonances.push_back(std::string("DH"));
    consonances.push_back(std::string("F"));
    consonances.push_back(std::string("G"));
    consonances.push_back(std::string("HH"));
    consonances.push_back(std::string("JH"));
    consonances.push_back(std::string("K"));
    consonances.push_back(std::string("L"));
    consonances.push_back(std::string("M"));
    consonances.push_back(std::string("N"));
    consonances.push_back(std::string("NG"));
    consonances.push_back(std::string("P"));
    consonances.push_back(std::string("R"));
    consonances.push_back(std::string("S"));
    consonances.push_back(std::string("SH"));
    consonances.push_back(std::string("T"));
    consonances.push_back(std::string("TH"));
    consonances.push_back(std::string("V"));
    consonances.push_back(std::string("W"));
    consonances.push_back(std::string("Y"));
    consonances.push_back(std::string("Z"));
    consonances.push_back(std::string("ZH"));

    // Vowel->character map
    pronmap[std::string("AA")] = std::string("a");
    pronmap[std::string("AE")] = std::string("b");
    pronmap[std::string("AH")] = std::string("c");
    pronmap[std::string("AO")] = std::string("d");
    pronmap[std::string("AW")] = std::string("e");
    pronmap[std::string("AY")] = std::string("f");
    pronmap[std::string("EH")] = std::string("g");
    pronmap[std::string("ER")] = std::string("h");
    pronmap[std::string("EY")] = std::string("i");
    pronmap[std::string("IH")] = std::string("j");
    pronmap[std::string("IY")] = std::string("k");
    pronmap[std::string("OW")] = std::string("l");
    pronmap[std::string("OY")] = std::string("m");
    pronmap[std::string("UH")] = std::string("n");
    pronmap[std::string("UW")] = std::string("o");

    // Consonance->character map
    pronmap[std::string("B")]  = std::string("p");
    pronmap[std::string("CH")] = std::string("q");
    pronmap[std::string("D")]  = std::string("r");
    pronmap[std::string("DH")] = std::string("s");
    pronmap[std::string("F")]  = std::string("t");
    pronmap[std::string("G")]  = std::string("u");
    pronmap[std::string("HH")] = std::string("v");
    pronmap[std::string("JH")] = std::string("w");
    pronmap[std::string("K")]  = std::string("x");
    pronmap[std::string("L")]  = std::string("y");
    pronmap[std::string("M")]  = std::string("z");
    pronmap[std::string("N")]  = std::string("A");
    pronmap[std::string("NG")] = std::string("B");
    pronmap[std::string("P")]  = std::string("C");
    pronmap[std::string("R")]  = std::string("D");
    pronmap[std::string("S")]  = std::string("E");
    pronmap[std::string("SH")] = std::string("F");
    pronmap[std::string("T")]  = std::string("G");
    pronmap[std::string("TH")] = std::string("H");
    pronmap[std::string("V")]  = std::string("I");
    pronmap[std::string("W")]  = std::string("J");
    pronmap[std::string("Y")]  = std::string("K");
    pronmap[std::string("Z")]  = std::string("L");
    pronmap[std::string("ZH")] = std::string("M");

    // all phonemes as a collection
    phonemes.reserve( vowels.size() + consonances.size() );
    phonemes.insert( phonemes.end(), vowels.begin(), vowels.end() );
    phonemes.insert( phonemes.end(), consonances.begin(), consonances.end() );
  }

  std::vector<std::string>& get_vowels()
  {
    return vowels;
  }

  std::vector<std::string>& get_consonances()
  {
    return consonances;
  }

  std::map<std::string,std::string>& get_pronmap()
  {
    return pronmap;
  }

  std::vector<std::string>& get_phonemes()
  {
    return phonemes;
  }

};

/* A class that is used to carry out operations on pronunciation data.
 * Initialized with static data, that is why it is implemented as a class and
 * not functions */
class PronopsOperator {

  public:

  // static data the functions use
  static PronopsStaticData data;


  /* Return a vector of strings containing only pronouncable phonemes (i.e.,
   * remove word break characters '|' and numbers*/
  std::vector<std::string> pron_only_phonemes(std::vector<std::string>& words)
  {
    return strops::remove_strings_not_in(words,
        PronopsOperator::data.get_phonemes());
  }

  /* Return a vector of strings containing a regular expression representation
   * of the pronunciation. Accepts a vector of strings as pronunciation. */
  std::vector<std::string> pron_to_regex(std::vector<std::string>& words)
  {
    std::vector<std::string> result = words;
    strops::map_strings(result,
        PronopsOperator::data.get_pronmap());
    return result;
  }

  /* make a regular expression describing the desired pronunciation from a
   * simple expression like "3 AH ER", which means find a sentence of 3
   * syllables, the last 2 being AH and ER. The corresponding regular
   * expression is ^[p-zA-M]*[a-o][p-zA-M]*c{1}[p-zA-M]*h{1}[p-zA-H]$ */
  /* default constructor */
  std::string ez_pron_regex(std::string& query)
  {
    std::string result("");
    std::vector<std::string> words = strops::separate_strings(query, ' ');
    
    if (!strops::is_numbers_only(words[0])) {
      std::cerr << "Error " << __LINE__ << ": First token must be a number."
        << std::endl;
      return result;
    }

    int numsylls = atoi(words[0].c_str());
    if (numsylls < 0)
      numsylls *= -1;

    if ((words.size() - 1) > numsylls) {
      std::cerr << "Error " << __LINE__ << ": More phonemes than syllables."
        << std::endl;
      return result;
    }

    // Put beginning of line character
    result.push_back('^');
    // The number of free syllables at the beginning
    int nfreesylls = numsylls - (words.size() - 1);
    while (nfreesylls-- > 0) {
      result.append("[p-zA-M]*"); // Match any non-vowel (non-syllable)
      result.append("[a-o]"); // Match a vowel (syllable) once
    }
    // Now put the specified vowels
    size_t i;
    for (i = 1; i < words.size(); ++i) {
      if (PronopsOperator::data.get_pronmap().find(words[i])
          == PronopsOperator::data.get_pronmap().end()) {
        std::cerr << "Error " << __LINE__ << ": Token " << words[i]
          << " not found in map." << std::endl;
        result.clear();
        return result;
      }
      std::string token = PronopsOperator::data.get_pronmap()[words[i]];
      result.append("[p-zA-M]*");
      result.append(token);
    }

    // append one last set of syllables and of line character to regex
    result.append("[p-zA-M]*$");

    return result;
  }

  PronopsOperator() { }

};

PronopsStaticData PronopsOperator::data;

/* Counts the number of syllables in a pronunciation. This just counts the
 * number of digits in the pronunciation as these indicate syllable stress in
 * the CMU Pronunciation dictionary, therefore the number of these numbers is
 * the number of syllables. */
static size_t
count_syllables(std::string& s)
{
  return strops::count_digits(s);
}

} // end of namespace pronops

#endif /* PRONOPS_H */
