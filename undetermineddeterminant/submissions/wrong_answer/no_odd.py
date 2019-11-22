n = int(input())

MOD = 998244353

fact = [1]
for i in range(1,1000001):
    fact.append(i*fact[i-1]%MOD)

if n % 2 == 1:
    print(0)
elif n == 2:
    print(-1 + MOD)
else:
    n2 = n//2
    ans = pow(n2, n2-2,MOD)*pow(2,n-2,MOD)*fact[n]*pow(fact[n2],MOD-2,MOD)*pow(pow(2,n2,MOD),MOD-2,MOD)*pow(pow(n,n-2,MOD),MOD-2,MOD)%MOD
    print(ans)
    
