calcFib :: Int -> Int
calcFib 0 = 0
calcFib 1 = 1
calcFib n = sumUpToN (n-1) + sumUpToN (n-2)
