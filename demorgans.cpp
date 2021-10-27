#include <cvc5/cvc5.h>
#include <iostream>

using namespace std;
using namespace cvc5::api;

int main(){
   Solver slv;

   slv.setLogic("QF_UFLIAFS");

   // Produce models
   slv.setOption("produce-models", "true");
   slv.setOption("output-language", "smt2");
   slv.setOption("sets-ext", "true");

   Sort boolean = slv.getBooleanSort();
   Sort set = slv.mkSetSort(boolean);


   // Verify De Morgans Law
   // ~(~A union ~B) = A intersection B
   Term A = slv.mkConst(set, "A");
   Term B = slv.mkConst(set, "B");

   Term notA = slv.mkTerm(COMPLEMENT, A);
   Term notB = slv.mkTerm(COMPLEMENT, B);
   Term notA_union_notB = slv.mkTerm(UNION, notA, notB);
   Term lhs = slv.mkTerm(COMPLEMENT, notA_union_notB);
   Term rhs = slv.mkTerm(INTERSECTION, A, B);

   Term lemma1 = slv.mkTerm(SUBSET, lhs, rhs);
   Term lemma2 = slv.mkTerm(SUBSET, rhs, lhs);
   Term theorem1 = slv.mkTerm(AND, lemma1, lemma2);
   Term theorem2 = slv.mkTerm(EQUAL, lhs, rhs);


   cout << "Should print entailed for all checks" << endl;
   cout << "check1 is " << theorem1 << endl;
   cout << "cvc5 reports that De Morgans Law"
        << " is " << slv.checkEntailed(theorem1) << endl;
   cout << "check2 is " << theorem2 << endl;
   cout << "cvc5 reports that De Morgans Law"
	<< " is " << slv.checkEntailed(theorem2) << endl;

   return 0;
}
