#ifndef SRC_SET_H_
#define SRC_SET_H_

namespace s21 {
class Set {
 public:
  Calculator(std::stack<CalcNode>& Stack, double input_x);
  double getResult();

 private:
  // data members
  double result;
  double input_x;
  std::stack<CalcNode>& Stack;
  std::stack<CalcNode> help;

  // help functions
  void calculation();
  void do_arifmetic_action(Types operation, double number_1, double number_2);
  void do_afunction_action(Types operation, double number_1);
};
}  // namespace s21

#endif  // SRC_SET_H_