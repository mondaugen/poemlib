/* Testing the regexpron library */

#include <regexpron.h>
#include <iostream>
#include <pronops.h> 

using namespace std;
using namespace kyotocabinet;

int
main (int argc, char **argv)
{
  
  if (argc != 2) {
    cerr << "Arguments are " << argv[0] << " pronunciation description." << endl;
    return 1;
  }

  // open sentence database
  PolyDB db;

  // Open the db
  if (!db.open("../pron/sentence-pronounce.kch")) {
    cerr << "open error: " << db.error().name() << endl;
  }

  string ez(argv[1]); // The easy description
  
  pronops::PronopsOperator pops;
  string re = pops.ez_pron_regex(ez);

  if (re == string("")) {
    cerr << "Error parsing query " << ez << endl;
    return 1;
  }

  cerr << "Searching for query " << re << endl;

  vector<string> results = regexpron::find_strings_with_pron(db, re);

  for (vector<string>::iterator it = results.begin();
      it != results.end(); ++it) {
    cout << *it << endl;
  }

  if (!db.close()) {
    cerr << "DB close error: " << db.error().name() << endl;
  }

  return 0;

}


