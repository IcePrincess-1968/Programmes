ans=[]
l=200

def dfs(cur):
	Bin=bin(cur)[2:]
	rn=int(Bin)
	fBin=bin(rn)[2:]
	Len=len(Bin)
	while Len<=l:
		if Len>=len(fBin) or fBin[-Len-1]=='0':
			ans.append(cur|(1<<Len))
			dfs(cur|(1<<Len))
		else:
			return
		Len+=1

for i in range(l):
	ans.append(1<<i)
	dfs(1<<i)
ans.sort()
with open('binary.in') as fread:
	rnk=int(fread.read())
with open('binary.out','w') as fwrite:
	fwrite.write(str(bin(ans[rnk-1])[2:])+'\n')