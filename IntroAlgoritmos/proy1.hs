-- ejercicio 1 a

esCero :: Int -> Bool
esCero n = (n == 0)

-- ejercicio 1 b

esPositivo :: Int -> Bool
esPositivo n = (n >= 0)

-- ejercicio 1 c
esVocal :: Char -> Bool
esVocal x = (x == 'a') || (x == 'e') || (x == 'i') || (x == 'o') || (x == 'u') 

-- ejercicio 2 a
paratodo :: [Bool] -> Bool
paratodo [] = True
paratodo (x:xs) | (x == True) = x && (paratodo xs)
                | otherwise = False

-- ejercicio 2 b
sumatoria :: [Int] -> Int
sumatoria [] = 0
sumatoria (n:ns) = n + (sumatoria ns) 

-- ejercicio 2 c
productoria :: [Int] -> Int
productoria [] = 1
productoria (n:ns) = n * (productoria ns)

-- ejercicio 2 d 
factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n-1) 

-- ejercicio 2 e 
promedio :: [Int] -> Int
promedio [] = 0
promedio ns = div (sumatoria ns) (length ns)

-- ejercicio 3 
pertenece :: Int -> [Int] -> Bool
pertenece _ [] = False
pertenece x (n:ns) = (x == n) || pertenece x ns

-- ejercicio 4 a 
paratodo' :: [a] -> (a -> Bool) -> Bool
paratodo' [] _ = True
paratodo' (n:ns) t = (t n) && (paratodo' ns t)

-- ejercicio 4 b
existe' :: [a] -> (a -> Bool) -> Bool 
existe' [] _ = False
existe' (n:ns) t = (t n) || existe' ns t

-- ejercicio 4 c 
sumatoria' :: [a] -> (a -> Int) -> Int
sumatoria' [] _ = 0
sumatoria' (n:ns) t = t n + sumatoria' ns t 

-- ejercicio 4 d 
productoria' :: [a] -> (a -> Int) -> Int
productoria' [] _ = 1
productoria' (n:ns) t = t n * productoria' ns t

-- ejercicio 5
paratodo'' :: [a] -> (a -> Bool) -> Bool
paratodo'' ns t = paratodo' ns t 

-- ejercicio 6 a 
todosPares :: [Int] -> Bool
todosPares ns = paratodo' ns even

-- ejercicio 6 b 

esMultiplo :: Int -> Int -> Bool
esMultiplo x n = (mod x n == 0)

hayMultiplo :: Int -> [Int] -> Bool
hayMultiplo x ns = existe' ns (`esMultiplo` x)

-- ejercicio 6 c 
cuad :: Int -> Int 
cuad n = n * n

sumaCuadrados :: Int -> Int
sumaCuadrados n = sumatoria' [0..n-1] cuad

-- ejercicio 6 d
factorial' :: Int -> Int
factorial' n = factorial n

-- ejercicio 6 e 
esPar :: [Int] -> [Int]
esPar [] = []
esPar (n:ns) | (mod n 2 == 0) = n:(esPar ns)
             | otherwise = esPar ns

multiplicaPares :: [Int] -> Int
multiplicaPares [] = 1
multiplicaPares ns = productoria (esPar ns)

{- ejercicio 7
 map: modifica cada elemento de la lista
 filter: solo devuelve los elementos en la lista que cumplan una condicion

 map succ [1,(-4),6,2,(-8)] = [2,-3,7,3,-7]

 filter esPositivo [1,(-4),6,2,(-8)] = [1,6,2]
-}

-- ejercicio 8 a 

duplica :: [Int] -> Int
duplica [] = 0
duplica (n:ns) = n*2 + duplica ns

-- ejercicio 8 b
porDos :: Int -> Int
porDos n = n * 2

duplica' :: [Int] -> Int
duplica' ns = sumatoria (map porDos ns)

-- ejercicio 9 a
soloPares :: [Int] -> [Int]
soloPares [] = []
soloPares (n:ns) | (even n) = n:soloPares ns
                 | otherwise = soloPares ns

-- ejercicio 9 b
soloPares' :: [Int] -> [Int]
soloPares' [] = []
soloPares' ns = filter even ns

-- ejercicio 9 c 
soloPares'' :: [Int] -> [Int]
soloPares'' ns = esPar ns

-- ejercicio 10 a 

primIgualesA :: Ord a => a -> [a] -> [a] 
primIgualesA _ [] = []
primIgualesA n (a:as) | (n==a) = a:(primIgualesA n as)
                      | otherwise = []

-- ejercicio 10 b
primIgualesA' :: Ord a => a -> [a] -> [a] 
primIgualesA' _ [] = []
primIgualesA' n as = takeWhile (== n) as

-- ejercicio 11 a 
primIguales :: Ord a => [a] -> [a]
primIguales [] = []
primIguales [a] = [a]
primIguales (a:as) |(a==(head as)) = a:primIguales as
                   | otherwise = [a]

-- ejercicio 11 b
primIguales' :: Ord a => [a] -> [a]
primIguales' as = primIgualesA' (head as) as

{-  ejercicio 12

a)  f :: (a, b) -> ...
    f x = ...
    
    esta bien tipado en el caso de que 
    x = (a, b).

b) f :: (a, b) -> ...
   f (x, y) = ...
    esta bien tipada en el caso que x = a , y = b.

c) f :: [(a,b)] -> ...
   f (a, b) = ...
    Esta mal tipada.

d) f :: [(a,b)] -> ...
   f (x:xs) = ...
    Esta bien tipada, pero no considera el caso en
    el que la lista es vacia.

e) f :: [(a,b)] -> ...
   f ((x, y): ((a, b) : xs) = ...
    Esta bien tipada, pero no considera el caso en
    el que la lista es vacia.

f) f :: [(Int, a)] -> ...
   f [(0, a)] = ...
    Esta mal tipado, 0 no es una variable del tipo
    Int.

g) f :: [(Int, a)] -> ...
   f ((x, 1):xs) = ...
    Esta mal tipado, da una constante, a = 1.

h) f :: [(Int, a)] -> ...
   f ((1, x):xs) = ...
    Mal tipado, da una constante Int = 1.

i) f :: (Int -> Int) -> Int -> ...
   f a b = ...
    Esta bien tipada en el caso en el que a 
    sea una funcion que va de Int -> Int
    y b sea un Int.

j) f :: (Int -> Int) -> Int -> ...
   f a 3 = ...
    Esta mal tipada, 3 es una constante.

k) f :: (Int -> Int) -> Int -> ...
   f 0 1 2 = ...
    Esta mal tipado, no existe ninguna variable.

l) f :: a -> (a -> a) -> ...
   f a g = ...
    Esta bien tipada en el caso en el que g se una
    funcion del tipo (a -> a).            

-}

{-  ejercicio 13

 a) f :: (a, b) -> b
    f (x, y) = y

 b) f :: (a, b) -> c 
    f (x, y) = z

 c) f :: a -> b
    f x = y

 d) f :: (a -> b) -> a -> b
    f t x = y 
    Suponiendo que t :: x -> y

 e) f :: (a -> b) -> [a] -> [b]
    f t xs = ys

    t :: x -> y.

 f) f :: (a -> b) -> a -> c
    f t x = z

    t :: x -> y.
    
 g) f :: (a -> b) -> (b -> c) -> a -> c
    f t u x = z

    t :: x -> y.
    u :: z -> a.
-}