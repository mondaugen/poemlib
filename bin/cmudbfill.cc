/**
 * Fill a database with <word>:<pronunciation> pairs
 */

#include <kcpolydb.h> 
#include <cstring> 

using namespace std;
using namespace kyotocabinet;

int
main(int argc, char **argv)
{
  if (argc != 2) {
    cerr << "Useage:\n" << argv[0] << " <path to resulting database>\n"
      << "The cmudict is given through stdin redirection (see README).\n"
      << "The resulting database path should end in an ending supported by kyoto cabinet.\n"
      << ".kch is recommended (see README)." << endl;
    return 1;
  }

  // create database object
  PolyDB db;

  // open the database
  if (!db.open(argv[1], PolyDB::OWRITER | PolyDB::OCREATE)) {
    cerr << "open error: " << db.error().name() << endl;
  }

  string cmuline;
  // read in a line from standard in (where we're inputting cmudict)
  while ( true ) {

    cmuline.clear();

    getline(cin, cmuline);

    if (cin.eof())
      break;

    vector<string> tokens;

    strsplit(cmuline, ' ', &tokens);

    string value;
    
    if ((tokens.size() >= 2) && (tokens[0].compare(0,3,";;;") != 0)) {
      vector<string>::iterator it;
      for (it = (tokens.begin()+2);
          it < (tokens.end()-1);
          ++it) {

        value.append(*it);
        value.push_back(' ');

      }

      value.append(*it);


      if (!db.set(tokens[0].c_str(),value.c_str())) {
        cerr << "set error: " << db.error().name() << endl;
      } else {
        cerr << "set key: " << tokens[0] << " to: " << value << endl;
      }

    }

  }

  if (!db.close()) {
    cerr << "close error: " << db.error().name() << endl;
  }

  return(0);

}


  
