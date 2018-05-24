class Task {
    using func_t = function<void()>;
    func_t f;
public:
    Task(func_t func) : f(func) {}
    // return: exec time [ms]
    ll exec() {
        clock_t start = clock();
        f();
        clock_t end = clock();
        return ll(end - start);
    }
};
