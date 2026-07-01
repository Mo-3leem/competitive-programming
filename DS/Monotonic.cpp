template<typename T>
struct Monotonic {

    //=====================================================
    // Previous Greater
    // prv[i] = index of previous element > a[i]
    // -1 if doesn't exist
    //=====================================================
    static vector<int> prevGreater(const vector<T>& a) {
        int n = a.size();
        vector<int> prv(n, -1);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] <= a[i])
                st.pop();

            if (!st.empty())
                prv[i] = st.top();

            st.push(i);
        }

        return prv;
    }

    //=====================================================
    // Previous Smaller
    //=====================================================
    static vector<int> prevSmaller(const vector<T>& a) {
        int n = a.size();
        vector<int> prv(n, -1);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] >= a[i])
                st.pop();

            if (!st.empty())
                prv[i] = st.top();

            st.push(i);
        }

        return prv;
    }

    //=====================================================
    // Next Greater
    //=====================================================
    static vector<int> nextGreater(const vector<T>& a) {
        int n = a.size();
        vector<int> nxt(n, -1);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] <= a[i])
                st.pop();

            if (!st.empty())
                nxt[i] = st.top();

            st.push(i);
        }

        return nxt;
    }

    //=====================================================
    // Next Smaller
    //=====================================================
    static vector<int> nextSmaller(const vector<T>& a) {
        int n = a.size();
        vector<int> nxt(n, -1);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()] >= a[i])
                st.pop();

            if (!st.empty())
                nxt[i] = st.top();

            st.push(i);
        }

        return nxt;
    }

    //=====================================================
    // Sliding Window Maximum
    // returns indices of maximums
    //=====================================================
    static vector<int> slidingMaximum(const vector<T>& a, int k) {
        deque<int> dq;
        vector<int> ans;

        for (int i = 0; i < (int)a.size(); i++) {

            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            while (!dq.empty() && a[dq.back()] <= a[i])
                dq.pop_back();

            dq.push_back(i);

            if (i >= k - 1)
                ans.push_back(dq.front());
        }

        return ans;
    }

    //=====================================================
    // Sliding Window Minimum
    // returns indices of minimums
    //=====================================================
    static vector<int> slidingMinimum(const vector<T>& a, int k) {
        deque<int> dq;
        vector<int> ans;

        for (int i = 0; i < (int)a.size(); i++) {

            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            while (!dq.empty() && a[dq.back()] >= a[i])
                dq.pop_back();

            dq.push_back(i);

            if (i >= k - 1)
                ans.push_back(dq.front());
        }

        return ans;
    }
};
