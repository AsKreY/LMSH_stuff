S = {"S": ["AF", "BR", ""], "F": ["BR", "AF"], "A": ["BR"], "B": ["LF", "["], "R": ["]"], "L": ["["]}
Q = "SFABRL"
w = "[[]"
n = len(w)
N = len(Q)
P = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(N)]
for a in range(n):
    for j in range(n-a):
        k = j + a
        if a == 0:
            for i in range(N):
                if w[j] in S[Q[i]]:
                    P[i][j][k] = 1
                    print("{} -> {}".format(Q[i], w[j:k + 1]))
        else:
            for i in range(N):
                for h in range(len(S[Q[i]])):
                    bool1, bool2 = 0, 0
                    for m in range(a):
                        if len(S[Q[i]][h]) < 2:
                            continue
                        bool1 = max(P[Q.find(S[Q[i]][h][0])][j][j+m], bool1)
                        bool2 = max(P[Q.find(S[Q[i]][h][1])][j+m+1][k], bool2)
                        if bool1 and bool2:
                            P[i][j][k] = 1
                            print("{} -> {}".format(Q[i], w[j:k+1]) + S[Q[i]][h])
            
        pass
print(P[0][0][n-1])
print(P)
