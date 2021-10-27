#include <iostream>
#include <cvc5/cvc5.h>

using namespace std;
using namespace cvc5::api;

int main(){
   Solver slv;

   Sort real = slv.getRealSort();
   Sort integer = slv.getIntegerSort();

   // Variables
   Term a = slv.mkConst(real, "a");
   Term b = slv.mkConst(real, "b");
   Term c = slv.mkConst(integer, "c");

   // Constants
   Term neg_one = slv.mkInteger(-1);

   // Terms
   Term ac = slv.mkTerm(MULT, a, c);
   Term bc = slv.mkTerm(MULT, b, c);

   // Formulas
   Term a_lt_b = slv.mkTerm(LT, a, b);
   Term c_equal_neg_one = slv.mkTerm(EQUAL, c, neg_one);

   Term assertions = slv.mkTerm(AND, a_lt_b, c_equal_neg_one);

   cout << "Given the assertions " << assertions << endl;
   slv.assertFormula(assertions);

   slv.push();
   Term ac_gt_bc = slv.mkTerm(GT, ac, bc);
   cout << "Prove that " << ac_gt_bc << " with cvc5." << endl;
   cout << "Should output entailed: "
        << slv.checkEntailed(ac_gt_bc) << endl;
   slv.pop();

   return 0;
}
