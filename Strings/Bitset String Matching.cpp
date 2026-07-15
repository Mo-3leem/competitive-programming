//==============================================================
// Bitset String Matching (Exact Pattern Matching)
//--------------------------------------------------------------
// Finds every occurrence of pattern P inside text T.
//
// Best when:
//   ✔ Small alphabet (e.g. lowercase letters, DNA, binary strings)
//   ✔ Many queries on the same text
//   ✔ Need exact substring matching
//   ✔ Need wildcard matching (skip '?')

//--------------------------------------------------------------
// Preprocessing:
//   Time : O(n)
//   Space: O(ALPHABET * n)
//          = 26 * n bits for lowercase letters
//
// Each Query:
//   Time : O(|P| * n / 64)
//   Space: O(n) bits (temporary bitset)
//==============================================================

const int MAXN = 200000 + 5;

bitset<MAXN> pos[26];

//--------------------------------------------------------------
// Build bitsets for the text.
// Call ONCE if the text is fixed.
//--------------------------------------------------------------
void build(const string &text) {

    for (int c = 0; c < 26; c++)
        pos[c].reset();

    for (int i = 0; i < (int)text.size(); i++)
        pos[text[i] - 'a'][i] = 1;
}

//--------------------------------------------------------------
// Return all starting indices where pattern appears.
//
// Example:
// text    = "ababcab"
// pattern = "abc"
//
// returns {2}
//
//--------------------------------------------------------------
vector<int> match(const string &pat, int n) {

    bitset<MAXN> ok;
    ok.set(); 

    for (int i = 0; i < (int)pat.size(); i++) {
        ok &= (pos[pat[i] - 'a'] >> i);
    }

    vector<int> ans;

    for (int i = 0; i + (int)pat.size() <= n; i++)
        if (ok[i])
            ans.push_back(i);

    return ans;
}
