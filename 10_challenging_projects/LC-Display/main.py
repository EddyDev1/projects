import sys

with open("i.txt", "r") as file:
  for line in file.readlines():
    data = line.strip().split(" ")
    
    s, n = int(data[0]), data[1]
    r, c = s * 2 + 3, s + 2
    
    vhs = '|- '
    temps = [['' for _ in range(len(n))] for _ in range(r)]


    for col in range(len(temps[0])):
      match n[col]:
        case '1':
          for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
              temps[_][col] = vhs[2]
            else:
              temps[_][col] = vhs[0] + (s - 1) * vhs[2]
        case '2':
          for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
              temps[_][col] = s * vhs[2] + s * vhs[1]
            elif _ > 0 and _ < r // 2:
              temps[_][col] = ((s + 1) * vhs[2]) + vhs[0]
            else:
              temps[_][col] = vhs[0] + ((s + 1) * vhs[2])
        case '3':
          for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
              temps[_][col] = (s * vhs[2]) + s * vhs[1] + (vhs[2] * s)
            else:
              temps[_][col] = (vhs[2] * (s + 1)) + vhs[0] + (vhs[2] * s)
        case '4':
          for _ in range(r):        
            if _ == 0 or _ == r - 1:
              temps[_][col] = ((s + 1) * vhs[2]) + vhs[2] + ((s) * vhs[2])
            elif _ > 0 and _ < r // 2:
              temps[_][col] = vhs[0] + s * vhs[2] + vhs[0] + s * vhs[2]
            elif _ == r // 2:
              temps[_][col] = ((s) * vhs[2]) + s * vhs[1] + (s * vhs[2])
            else:
              temps[_][col] = ((s + 1) * vhs[2]) + vhs[0] + s * vhs[2]
        case '5':
          for _ in range(r):
            if _ == 0 or _ == r // 2 or _ == r - 1:
              temps[_][col] = ((s) * vhs[2]) + s * vhs[1]
            elif _ > 0 and _ < r // 2:
              temps[_][col] =  vhs[0]
            else:
              temps[_][col] = ((s + 1) * vhs[2]) + vhs[0]


    for t in temps:
      n = len(t)
      s = ""
        
      for i in range(n):
        s += t[i]
        
      print(s)