-- 1) a)
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
data Carrera = Matematica | Fisica | Computacion | Astronomia deriving (Show, Eq, Ord)

-- 1) b)

titulo :: Carrera -> String
titulo Matematica = "Licenciatura en Matemática"
titulo Fisica = "Licenciatura en Fisica"
titulo Computacion = "Licenciatura en Computacion"
titulo Astronomia = "Licenciatura en Astronomia"

titulo' :: Carrera -> String
titulo' a = "Licenciatura en " ++ show a
-- 2) a)
{- Modifico la clase "Carrera" para poder obtener los resultados que me piden  en el ejercicio. Le agregue  deriving  (Show, Eq, Ord)-}

-- 3) a)

type Ingreso = Int

data Cargo = Titular | Asociado | Adjunto | Asistente | Auxiliar deriving (Show, Eq)

data Area = Administrativa | Ensenanza | Economica | Postgrado deriving (Show, Eq)

data Persona = Decane | Docente Cargo | NoDocente Area | Estudiante Carrera Ingreso deriving (Show, Eq)

-- 3) b)

--Docente :: Cargo -> Persona

-- 3) c)

cuantos_doc :: [Persona] -> Cargo -> Int
cuantos_doc [] _ = 0
cuantos_doc (x:xs) c | x == Docente c = 1 + cuantos_doc xs c
                   | otherwise = cuantos_doc xs c

-- 3) d)

cuantos_doc' :: [Persona] -> Cargo -> Int
cuantos_doc' xs c = length (filter (==Docente c) xs)

-- 4) a)

primerElemento :: [a] -> Maybe a
primerElemento [] = Nothing
primerElemento (x:_) = Just x

-- 5)
data Cola = VaciaC | Encolada Persona Cola deriving (Show)

-- a) 1)

atender' :: Cola -> Cola
atender' (Encolada p VaciaC) = VaciaC
atender' (Encolada p c) = Encolada p (atender' c)

atender :: Cola -> Maybe Cola
atender VaciaC = Nothing
atender c = Just (atender' c)

 -- a) 2)

encolar :: Persona -> Cola -> Cola
encolar = Encolada
 -- a) 3)

docente :: Cargo -> Persona -> Bool
docente Titular (Docente Titular) = True
docente Asociado (Docente Asociado) = True
docente Adjunto (Docente Adjunto) = True
docente Asistente (Docente Asistente) = True
docente Auxiliar (Docente Auxiliar) = True
docente _ _ = False

busca :: Cola -> Cargo -> Maybe Persona
busca VaciaC _ = Nothing
busca (Encolada persona cola) cargo |docente cargo persona = Just persona  |otherwise = busca cola cargo
-- b) Cola se parace al tipo Lista
-- 6)

data ListaAsoc a b = Vacia | Nodo a b (ListaAsoc a b) deriving (Show)
-- Ej

type Diccionario = ListaAsoc String String
type Padron = ListaAsoc Int String

-- a)

type GuiaTelefonica = ListaAsoc String Int

-- b) 1)

la_long :: ListaAsoc a b -> Int
la_long Vacia = 0
la_long (Nodo _ _ la) = 1 + la_long la

-- b) 2)

la_concat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b
la_concat Vacia ys = Vacia
la_concat (Nodo a b xs) ys = Nodo a b (la_concat xs ys)

-- b) 3)

la_pares :: ListaAsoc a b -> [(a, b)]
la_pares Vacia = []
la_pares (Nodo a b ls) = (a, b):la_pares ls

-- b) 4)

la_busca :: Eq a => ListaAsoc a b -> a -> Maybe b
la_busca Vacia _ = Nothing
la_busca (Nodo a b ls) c | a == c = Just b
                          | otherwise = Nothing

-- b) 5)

la_borrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b
la_borrar _ Vacia = Vacia
la_borrar p (Nodo a b y) | p == a = y
                         | otherwise = Nodo a b (la_borrar p y)

-- 7)

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a)


a_long :: Arbol a -> Int
a_long Hoja = 0
a_long (Rama x _ y) = 1 + a_long x + a_long y


a_hojas :: Arbol a -> Int
a_hojas Hoja = 1
a_hojas (Rama x _ y) = a_hojas x + a_hojas y


a_inc :: Num a => Arbol a -> Arbol a
a_inc Hoja = Hoja
a_inc (Rama x a y) = Rama (a_inc x) (a + 1) (a_inc y)


a_map :: (a -> b) -> Arbol a -> Arbol b
a_map _ Hoja = Hoja
a_map f (Rama x a y) = Rama (a_map f x) (f a) (a_map f y)


a_inc' :: Num a => Arbol a -> Arbol a
a_inc' = a_map (+1)
