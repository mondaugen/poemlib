/* Get all lines in a given database of sentence/pronunciation pairs that match
 * the specified rhyming pattern */

#include <regexpron.h>
#include <iostream>
#include <pronops.h> 
#include <cstdlib> 
#include <algorithm> 
#include <unistd.h>
#include <time.h> 

using namespace std;
using namespace kyotocabinet;

// A better random number generator than that supplied by STL
int myrandom (int i) { return (int)random()%i; }

int
main (int argc, char **argv)
{
  
  if ((argc != 3) && (argc != 4)) {
    cerr << "Useage:\n" << argv[0] << " <sentence database> <pronunciation description> "
      "<number of sentences to output>\n" << "See README for details." << endl;
    return 1;
  }

  // open sentence database
  PolyDB db;

  // Open the db
  if (!db.open(argv[1])) {
    cerr << "open error: " << db.error().name() << endl;
  }

  string ez(argv[2]); // The pronunciation description
  
  pronops::PronopsOperator pops;
  string re = pops.ez_pron_regex(ez);

  if (re == string("")) {
    cerr << "Error parsing query " << ez << endl;
    return 1;
  }

  cerr << "Searching for query " << re << endl;

  vector<string> results = regexpron::find_strings_with_pron(db, re);

  // seed random number generator
  srandom(time(NULL));
  // shuffle the vector
  random_shuffle(results.begin(), results.end(), myrandom);

  size_t numresults;
  if (argc == 4) {
    numresults = strtoul(argv[3], NULL, 0);
  } else {
    numresults = 0;
  }


  if (numresults == 0) {
    for (vector<string>::iterator it = results.begin();
        it != results.end(); ++it) {
      cout << *it << endl;
    }
  } else {
    for (vector<string>::iterator it = results.begin();
        it != results.end(); ++it) {
      cout << *it << endl;
      if (--numresults == 0)
        break;
    }
  }


  if (!db.close()) {
    cerr << "DB close error: " << db.error().name() << endl;
  }

  return 0;

}


