s, n = 2, "32154"
r, c = 7, 4
vhs = '|- '
ans = []

for col in range(5):
  temp = [['' for _ in range(len(n))] for _ in range(r)]
  match n[col]:
    case '1':
        for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
                temp[_][col] = vhs[2]
            else:
                temp[_][col] = vhs[0]
    case '2':
        for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
                temp[_][col] = (s - 1) * vhs[2] + s * vhs[1]
            elif _ > 0 and _ < r // 2:
                temp[_][col] = ((s + 1) * vhs[2]) + vhs[0]
            else:
                temp[_][col] = vhs[0] + ((s + 1) * vhs[2]) 
    case '3':
        for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
                temp[_][col] = ((s - 1) * vhs[2]) + s * vhs[1] + (vhs[2] * (s))
            else:
                temp[_][col] = (vhs[2] * (s + 1)) + vhs[0] + (vhs[2] * (s-1))
    case '4':
        for _ in range(r):        
            if _ == 0 or _ == r - 1:
                temp[_][col] = ((s) * vhs[2]) + ((s + 2) * vhs[2])
            elif _ > 0 and _ < r // 2:
                temp[_][col] = (s - 1) * vhs[2] + vhs[0] + (s+1) * vhs[2] + vhs[0]
            elif _ == r // 2:
                temp[_][col] = ((s + 1) * vhs[2]) + s * vhs[1] + ((s - 1) * vhs[2])
            else:
                temp[_][col] = ((s + 3) * vhs[2]) + vhs[0]
    case '5':
        for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
                temp[_][col] = (s) * vhs[2] + s * vhs[1] + (s+1) * vhs[2]
            elif _ > 0 and _ < r // 2:
                temp[_][col] =  vhs[0] + s * vhs[2]
            else:
                temp[_][col] = (s+1) * vhs[2] + vhs[0]
          
  ans.append(temp)

final = [[] for _ in range(7)]
for i in range(5):
  for k in range(7):
    final[k].append(ans[i][k][i] + 15 * vhs[2])

for f in final:
  s = ""
  for i in range(len(f)):
    s += f[i]
    
  print(s)
  #print(f)
    