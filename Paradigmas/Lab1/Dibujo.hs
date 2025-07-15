module Dibujo where

-- Definir el lenguaje via constructores de tipo
data Dibujo a = Basica a 
                | Rotar (Dibujo a)
                | Rotar45 (Dibujo a)
                | Espejar (Dibujo a)
                | Apilar Float Float (Dibujo a) (Dibujo a)
                | Juntar Float Float (Dibujo a) (Dibujo a)
                | Encimar (Dibujo a) (Dibujo a)
                deriving (Eq, Show)

-- Composición n-veces de una función con sí misma.
comp :: (a -> a) -> Int -> a -> a
comp f n dib  | n == 0 = dib
              | n > 0 = comp f (n-1) (f dib)
              | otherwise = error "Poneme un numero positivo"

-- Rotaciones.
r45 :: Dibujo a -> Dibujo a
r45 dib = Rotar45 dib

r90 :: Dibujo a -> Dibujo a
r90 dib = Rotar dib

r180 :: Dibujo a -> Dibujo a
r180 dib = comp r90 2 dib

r270 :: Dibujo a -> Dibujo a
r270 dib = comp r90 3 dib

-- Funciones Constructoras

espejar :: Dibujo a -> Dibujo a
espejar dib = Espejar dib

apilar :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
apilar n m dib1 dib2 = Apilar n m dib1 dib2

juntar :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
juntar n m dib1 dib2 = Juntar n m dib1 dib2

encimar :: Dibujo a -> Dibujo a -> Dibujo a
encimar dib1 dib2 = Encimar dib1 dib2

-- Pone una figura sobre la otra, ambas ocupan el mismo espacio.z
(.-.) :: Dibujo a -> Dibujo a -> Dibujo a
(.-.) a b = apilar 1.0 1.0 a b


-- Pone una figura al lado de la otra, ambas ocupan el mismo espacio.
(///) :: Dibujo a -> Dibujo a -> Dibujo a
(///) a b = juntar 1.0 1.0 a b

-- Superpone una figura con otra.
(^^^) :: Dibujo a -> Dibujo a -> Dibujo a
(^^^) a b = encimar a b

-- Dadas cuatro dibujos las ubica en los cuatro cuadrantes.
cuarteto :: Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a
cuarteto dib1 dib2 dib3 dib4 = (dib1 /// dib2) .-. (dib3 /// dib4)

-- Una dibujo repetido con las cuatro rotaciones, superpuestas.
encimar4 :: Dibujo a -> Dibujo a
encimar4 dib = dib ^^^ (r90 dib) ^^^ (r180 dib) ^^^ (r270 dib)


-- Cuadrado con la misma figura rotada i * 90, para i ∈ {0, ..., 3}.
-- No confundir con encimar4!
ciclar :: Dibujo a -> Dibujo a
ciclar dib = cuarteto dib (r90 dib) (r180 dib) (r270 dib)


-- Transfomar un valor de tipo a como una Basica.
pureDib :: a -> Dibujo a
pureDib x = Basica x --no termino de entender qué hace esta función

-- map para nuestro lenguaje.
--cada dibujo puede estar compuesto de otros dibujos, entonces le tendria que aplicar f a todos los componentes hasta llegar a basica
mapDib :: (a -> b) -> Dibujo a -> Dibujo b
mapDib f (Basica x) =  Basica (f x)
mapDib f (Rotar x) = Rotar(mapDib f x)
mapDib f (Rotar45 x) = Rotar45(mapDib f x)
mapDib f (Espejar x) = Espejar (mapDib f x)
mapDib f (Apilar a b x y) = Apilar a b (mapDib f x) (mapDib f y)
mapDib f (Juntar a b x y) = Juntar a b (mapDib f x) (mapDib f y)
mapDib f (Encimar x y) = Encimar (mapDib f x) (mapDib f y)
 
-- Funcion de fold para Dibujos a
foldDib :: (a -> b) -> (b -> b) -> (b -> b) -> (b -> b) -> -- x a basica, rotar45, rotar, espejar
       (Float -> Float -> b -> b -> b) -> -- apilar
       (Float -> Float -> b -> b -> b) -> --juntar
       (b -> b -> b) -> --encimar
       Dibujo a -> b --dibujo q se va a plegar y convertirse en b
       
foldDib f r1 r2 e1 a j e2 dib = case dib of
    Basica a           -> f a
    Rotar d            ->  r1      (foldDib f r1 r2 e1 a j e2 d)
    Rotar45 d          ->  r2      (foldDib f r1 r2 e1 a j e2 d)
    Espejar d          ->  e1      (foldDib f r1 r2 e1 a j e2 d)
    Apilar x y  d1 d2   ->  a x y (foldDib f r1 r2 e1 a j e2 d1) (foldDib f r1 r2 e1 a j e2 d2)
    Juntar x y d1 d2   ->  j x y (foldDib f r1 r2 e1 a j e2 d1) (foldDib f r1 r2 e1 a j e2 d2)
    Encimar d1 d2      ->  e2 (foldDib f r1 r2 e1 a j e2 d1) (foldDib f r1 r2 e1 a j e2 d2)
