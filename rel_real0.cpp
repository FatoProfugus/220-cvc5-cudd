#include <iostream>

#include <cvc5/cvc5.h>

using namespace std;

using namespace cvc5::api;

int main(){
   Solver slv;
   //slv.setLogic("QF_LIRA");

   Sort real = slv.getRealSort();
   Sort integer = slv.getIntegerSort();

   // Variables
   Term a = slv.mkConst(real, "a");
   Term b = slv.mkConst(real, "b");
   Term c = slv.mkConst(real, "c");

   // Constants
   Term zero = slv.mkInteger(0);

   // Terms
   Term ac = slv.mkTerm(MULT, a, c);
   Term bc = slv.mkTerm(MULT, b, c);

   // Formulas
   Term a_lt_b = slv.mkTerm(LT, a, b);
   Term zero_lt_c = slv.mkTerm(LT, zero, c);

   Term assertions = slv.mkTerm(AND, a_lt_b, zero_lt_c);

   cout << "Given the assertions " << assertions << endl;
   slv.assertFormula(assertions);

   slv.push();
   Term ac_lt_bc = slv.mkTerm(LT, ac, bc);
   cout << "Prove that " << ac_lt_bc << " with cvc5." << endl;
   cout << "Should output entailed: "
	<< slv.checkEntailed(ac_lt_bc) << endl;
   slv.pop();

   return 0;
}
