/**
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * 
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * getMin() -- Retrieve the minimum element in the stack.
 */

class MinStack {
    public:
        void push(int x) {
            data_.push(x);
            if (min_.empty()) {
                min_.push(x);
            } else if (min_.top() >= x) {
                min_.push(x);
            }
        }

        void pop() {
            if (data_.top() == min_.top()) {
                min_.pop();
            }
            data_.pop();
        }

        int top() {
            return data_.top();
        }

        int getMin() {
            return min_.top();
        }
    private:
        stack<int> data_;
        stack<int> min_;
};
