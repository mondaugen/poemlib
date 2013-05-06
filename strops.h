#ifndef  STROPS_H
#define STROPS_H

/* Some common string operations */

#include <cstdio>
#include <cstring>
#include <cstddef>
#include <cctype>
#include <string> 
#include <vector>
#include <map> 
#include <kcutil.h> 

namespace strops {

/* Read in the next sentence from a file. Returns number of chars read (so 0 is
 * EOF was reached) Only loads printable ascii characters, otherwise loads a
 * space. */
static size_t
get_next_sentence(std::string& s, FILE *f)
{
  char c;
  size_t len = 0;
  while ( true ) {
    c = fgetc(f);
    if (c == EOF)
      return len;
    if ((c >= 32) && (c < 127)) {
      s.push_back(c);
    } else {
      s.push_back(' ');
    }
    len++;
    if ((c == '.') || (c == '?') || (c == '!')) {
      return len;
    }
  }
}

/* Remove punctuation that has nothing to do with pronunciation (ie. don't
 * remove "'") */
static std::string&
remove_unpron_punct(std::string& s)
{
  size_t i;
  size_t j = 0;
  char buf[s.length()+1];
  for (i = 0 ; i < s.length(); i++) {
    if ((!ispunct(s[i])) || (s[i] == '\''))
      buf[j++] = s[i];
  }
  s.clear();
  s.replace(0,j,buf,j);
  return s;
}

/* Remove punctuation at beginning and end of sentence */
static std::string&
remove_begin_end_punct(std::string& s)
{
  size_t i, j;
  i = 0;
  j = s.length()-1;
  while (ispunct(s[i]) || isspace(s[i]))
    i++;
  while (ispunct(s[j]) || isspace(s[i]))
    j--;
  std::string tmp(s,i,j-i+1);
  s = tmp;
  return s;
}

/* Replace unpronouncable punctuation with a given char */
static std::string&
replace_unpron_punct(std::string& s, char c)
{
  size_t i;
  for (i = 0; i < s.length(); i++) {
    if ((ispunct(s[i]) && (s[i] != '\'')))
      s[i] = c;
  }
  return s;
}

/* Remove numbers from string */
static std::string&
remove_numbers(std::string& s)
{
  size_t i;
  size_t j = 0;
  char buf[s.length()+1];
  for (i = 0 ; i < s.length(); i++) {
    if (!isdigit(s[i]))
      buf[j++] = s[i];
  }
  s.clear();
  s.replace(0,j,buf,j);
  return s;
}

/* Make all lower case */
static std::string&
str_to_lower(std::string& s)
{
  size_t i;
  for (i = 0; i < s.length(); i++)
    s[i] = tolower(s[i]);
  return s;
}

/* Make all upper case */
static std::string&
str_to_upper(std::string& s)
{
  size_t i;
  for (i = 0; i < s.length(); i++)
    s[i] = toupper(s[i]);
  return s;
}

/* Format the string so there is no white-space at the beginning and end and all
 * whitespace is the ' ' (space) character. That means no new lines. */
static std::string&
normalize_ws(std::string& s)
{
  size_t i = 0;
  size_t j = 0;
  char buf[s.length()+1];
  memset(buf, '\0', s.length()+1);
  /* skip over whitespace at beginning */
  while ((i < s.length()) && isspace(s[i]))
    i++;
  /* Go forward, copying characters, until we find whitespace. Copy one
   * whitespace character but don't start copying again until non-whitespace is
   * found */
  while (i < s.length()) {
    if (isspace(s[i])) {
      buf[j++] = ' ';
      while ((i < s.length()) && (isspace(s[i])))
        i++;
    } else {
      buf[j++] = s[i++];
    }
  }
  /* If there's 1 whitespace at the end, remove it. */
  if (buf[j-1] == ' ')
    buf[--j] = '\0';
  else
    buf[j] = '\0';
  s.clear();
  s.replace(0,j,buf,j);
  return s;
}

/* Sometimes you would only like certain phonemes from a pronunciation (i.e.,
 * the vowels). Pronunciations also contain auxiliary data like where the words
 * break (|). These can be filtered out using this function.
 */
/* Accept a vector of strings and a vector of allowed strings. Remove all the
 * strings in the first vector that are not in the second. Returns the result.
 * */
static std::vector<std::string>
remove_strings_not_in(std::vector<std::string>& a, std::vector<std::string>& b)
{
  std::vector<std::string> result;
  std::vector<std::string>::iterator ait;
  for (ait = a.begin(); ait != a.end(); ++ait) {
    if (find(b.begin(), b.end(), *ait) != b.end())
      result.push_back(*ait);
  }
  return result;
}

/* count the number of digit characters in a string */
static size_t
count_digits(std::string& s)
{
  std::string::iterator it;
  size_t sum = 0;
  for (it = s.begin(); it != s.end(); ++it)
    if (isdigit(*it))
      sum++;
  return sum;
}

/* map words in vector of strings according to map, or leave unchanged if no
 * match */
static std::vector<std::string>&
map_strings(std::vector<std::string>& a, std::map<std::string,std::string>& m)
{
  std::vector<std::string>::iterator ait;
  for (ait = a.begin(); ait != a.end(); ++ait) {
    if (!(m.find(*ait) == m.end()))
      *ait = m[*ait];
    // otherwise leave ait unchanged
  }
  return a;
}

/* convert a string with <sep> as separators into a vector containing the
 * separated strings. i.e., "the dog went", sep = ' ' -> {"the","dog","went"} */
static std::vector<std::string>
separate_strings(std::string& s, char sep)
{
  std::vector<std::string> result;
  kyotocabinet::strsplit(s, sep, &result);
  return result;
}

/* combine a vector of strings into one string with the substrings separated by
 * sep. The last string is not appended with sep. */
static std::string
combine_strings(std::vector<std::string>& s, std::string& sep)
{
  std::string result;
  std::vector<std::string>::iterator it;
  size_t i;
  for (i = 0; i < s.size(); ++i) {
    result.append(s[i]);
    if (i < (s.size() - 1))
      result.append(sep);
  }
  return result;
}

/* return 1 if a string is all numbers, 0 otherwise */
int
is_numbers_only(std::string& s)
{
  if(s.size() < 1)
    return 0; // string empty
  std::string::iterator it;
  for (it = s.begin(); it != s.end(); ++it) {
    if (!isdigit(*it))
      return 0;
  }
  return 1;
}

} // end of namespace strops
      

#endif /* STROPS_H */ 
