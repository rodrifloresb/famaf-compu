module Pred where

import Dibujo

type Pred a = a -> Bool

--Para la definiciones de la funciones de este modulo, no pueden utilizar
--pattern-matching, sino alto orden a traves de la funcion foldDib, mapDib 

-- Dado un predicado sobre básicas, cambiar todas las que satisfacen
-- el predicado por el resultado de llamar a la función indicada por el
-- segundo argumento con dicha figura.
-- Por ejemplo, `cambiar (== Triangulo) (\x -> Rotar (Basica x))` rota
-- todos los triángulos.
cambiar :: Pred a -> (a -> Dibujo  a) -> Dibujo a -> Dibujo a
cambiar p f = foldDib (\x -> if p x then f x else Basica x) Rotar Rotar45 Espejar Apilar Juntar Encimar

-- Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool
anyDib a dib = foldDib a id id id (\_ _ d1 d2 -> d1 || d2) (\_ _ d1 d2 -> d1 || d2) (\d1 d2 -> d1 || d2) dib  

-- Todas las básicas satisfacen el predicado.
allDib :: Pred a -> Dibujo a -> Bool
allDib a dib = foldDib a id id id (\_ _ d1 d2 -> d1 && d2) (\ _ _ d1 d2 -> d1 && d2) (\d1 d2 -> d1 && d2) dib

-- Hay 4 rotaciones seguidas.
esRot360 :: Pred (Dibujo a)
esRot360 d = (foldDib f1 
                      f2 
                      f3 
                      (\ count -> if count < 4.0 then 0.0 else count) 
                      (\_ _ c1 c2 -> if max c1 c2 < 4.0 then 0.0 else max c1 c2) 
                      (\_ _ c1 c2 -> if max c1 c2 < 4.0 then 0.0 else max c1 c2)
                      (\ c1 c2 -> if max c1 c2 < 4.0 then 0.0 else max c1 c2) 
                      d) >= 4.0 --folddib me devuelve un valor y yo lo tengo que analizar
            where

                f1 :: a -> Float
                f1 _ = 0.0 --basica 

                f2 :: Float -> Float
                f2 count = count + 1.0 --rotar 90

                f3 :: Float -> Float
                f3 count = count + 0.5 -- rot 45

                

                
-- Hay 2 espejados seguidos.
esFlip2 :: Pred (Dibujo a)
esFlip2 dib = (foldDib f1
                     (\ count -> if count < 2 then 0 else count) 
                     (\ count -> if count < 2 then 0 else count) 
                     f4
                     (\_ _ c1 c2 -> if max c1 c2 < 2 then 0 else max c1 c2) 
                     (\_ _ c1 c2 -> if max c1 c2 < 2 then 0 else max c1 c2)
                     (\ c1 c2 -> if max c1 c2 < 2 then 0 else max c1 c2)
                     dib) >= 2 
        where 
            
            f1 :: a -> Int  --Basica
            f1 _ = 0     
            
            f4 :: Int -> Int  --Espejar
            f4 count = count + 1


data Superfluo = RotacionSuperflua | FlipSuperfluo deriving(Eq, Show)

-- Chequea si el dibujo tiene una rotacion superflua
errorRotacion :: Dibujo a -> [Superfluo]
errorRotacion dib = if esRot360 dib then [RotacionSuperflua] else []

-- Chequea si el dibujo tiene un flip superfluo
errorFlip :: Dibujo a -> [Superfluo]
errorFlip dib = if esFlip2 dib then [FlipSuperfluo] else []

-- Aplica todos los chequeos y acumula todos los errores, y
-- sólo devuelve la figura si no hubo ningún error.
checkSuperfluo :: Dibujo a -> Either [Superfluo] (Dibujo a)
checkSuperfluo dib = if (errorRotacion dib ++ errorFlip dib) == [] 
                        then Right dib 
                        else Left (errorRotacion dib ++ errorFlip dib)



