h, m = map(int, input().split())

if m - 45 < 0:
    m = m + 60
    h = h - 1
    if h < 0:
        h = 23

m = m - 45

print(h, m)