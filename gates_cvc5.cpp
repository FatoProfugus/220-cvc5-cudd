#include <cvc5/cvc5.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <math.h>

using namespace cvc5::api;
using namespace std;

Term xor_chain(Solver& slv, int n){
   if(n == 1) return slv.mkTrue();
   return slv.mkTerm(XOR, slv.mkTrue(), xor_chain(slv, n-1));
}

Term xor_tree(Solver& slv, int n){
   if(n == 0) return slv.mkTrue();
   return slv.mkTerm(XOR, xor_tree(slv, n-1), xor_tree(slv, n-1));
}

Term xor_mesh(Solver& slv, int n){
   return slv.mkTerm(XOR, xor_chain(slv,n), xor_tree(slv,n));
}

void dispatch_command(string command, int literal_count, Solver& slv){
   if(command == "xor_chain"){
      Term T = slv.mkTrue();
      Term F = slv.mkFalse();
      Term res = xor_chain(slv, literal_count);
      Term simplified = slv.simplify(res);
      if((literal_count%2 == 0 and simplified != F) or
         (literal_count%2 == 1 and simplified != T)){
            cout << "faliure for xor_chain with size "
                 << literal_count << endl;
      }
      else{
         cout << "success for xor_chain with size "
              << literal_count << endl;
      }
      cout << "simplified chain: " << simplified << endl;
   }
   else if(command == "xor_tree"){
      Term T = slv.mkTrue();
      Term F = slv.mkFalse();
      Term res = xor_tree(slv, literal_count);
      Term simplified = slv.simplify(res);
      if(simplified != F){
            cout << "faliure for xor_tree with size "
                 << literal_count << endl;
      }
      else{
         cout << "success for xor_tree with size "
              << literal_count << endl;
      }
      cout << "simplified tree: " << simplified << endl;
   }
   else if(command == "xor_mesh"){
      Term T = slv.mkTrue();
      Term F = slv.mkFalse();
      Term res = xor_mesh(slv, literal_count);
      Term simplified = slv.simplify(res);
      if((literal_count%2 == 0 and simplified != F) or
         (literal_count%2 == 1 and simplified != T)){
            cout << "faliure for xor_mesh with size "
                 << literal_count << endl;
      }
      else{
         cout << "success for xor_mesh with size "
              << literal_count << endl;
      }
      cout << "simplified mesh: " << simplified << endl;
   }
   else{
      cerr << "invalid command: " << command << endl;
   }
}

void resolve_input(istream& infile, string filename,
                   Solver& slv)
{
   string line {};
   for(;;){
      getline(infile, line);
      if(infile.eof()) break;

      regex command_regex {R"((.*?)\s(.*?)\s*$)"};

      smatch result;
      if(regex_search(line, result, command_regex)){
         if(result[1] != "" and result[2] != ""){
            dispatch_command(result[1], stoi(result[2]), slv);
	 }
	 else{
           cerr << "invalid command: " << line << endl;
	 }
      }
      else{
	 cerr << "resolve_input() error: regex_search() failed" << endl;
      }
   }
}

int main(int argc, char** argv){
   int exit_status = EXIT_SUCCESS;
   Solver slv {};

   slv.setOption("produce-models", "true");
   slv.setOption("produce-unsat-cores", "true");

   slv.setLogic("ALL");

   if(argc == 1){
      resolve_input(cin, "-", slv);
   }
   for(int i = 1; i < argc; ++i){
      string filename = argv[i];
      if(filename == "-"){
         resolve_input(cin, filename, slv);
      }
      ifstream file {};
      file.open(filename);
      if(not file.is_open()){
         exit_status = 1;
	 cerr << argv[0] << ": " << filename << ": "
              << strerror(errno) << endl;
	 continue;
      }
      resolve_input(file, filename, slv);
      file.close();
   }

   return exit_status;
}
