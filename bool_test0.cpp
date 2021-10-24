#include <cvc5/cvc5.h>
#include <iostream>

using namespace cvc5::api;
using namespace std;

int main(){
   Solver slv {};
   Term a = slv.mkTrue();
   cout << "a = " << a << endl;
   Term b = slv.mkTrue();
   cout << "b = " << b << endl;
   Term c = slv.mkTerm(AND, a, b);
   cout << "c = " << c << endl;
   Term d = slv.simplify(c);
   cout << "Term d = slv.simplify(c);" << endl;
   cout << "d = " << d << endl;
   Term e = slv.mkFalse();
   cout << "e = " << e << endl;
   cout << "d does " << ((d==a) ? "== a" : "not == a") << endl;
   cout << "d does " << ((d==e) ? "== e" : "not == e") << endl;
   cout << endl;
   cout << "We will now verify that demorgans holds, "
	<< "i.e. !(!a or !b) == a and b" << endl;
   cout << endl;
   Term not_a = slv.mkTerm(NOT, a);
   Term not_b = slv.mkTerm(NOT, b);
   Term f = slv.mkTerm(OR, not_a, not_b);
   Term not_f = slv.mkTerm(NOT, f);
   cout << "not_a = " << not_a << endl;
   cout << "not_b = " << not_b << endl;
   cout << "f = " << f << endl;
   cout << "not_f = " << not_f << endl;
   cout << "c = " << c << endl;
   cout << "without slv.simplify() " << not_f << " does "
	<< ((not_f==c) ? "== " : "not == ")
        << c << endl;
   cout << "with slv.simplify() " << not_f << " does "
	<< ((slv.simplify(not_f)==slv.simplify(c)) ? "== " : "not == ")
	<< c << endl;
   cout << "this is only because we called slv.simplify() on both "
	<< endl << "not_f and c" << endl;
   cout << "this means in cvc5 terms that aren't simplified do not == "
	<< endl << "one another if they differ in any way" << endl << endl;
   cout << "to further illustrate this consider:" << endl;
   Term a2 = slv.mkTrue();
   Term b2 = slv.mkTrue();
   Term c2 = slv.mkTerm(AND, a2, b2);
   cout << "c = " << c << endl;
   cout << "c2 = " << c2 << endl;
   cout << "without slv.simplify() " << c << " does "
        << ((c==c2) ? "== " : "not == ")
        << c2 << endl;
   return 0;
}
