-- Sacar del esqueleto final!
module Interp where
import Graphics.Gloss
import Graphics.Gloss.Data.Vector
import qualified Graphics.Gloss.Data.Point.Arithmetic as V

import Dibujo

-- Gloss provee el tipo Vector y Picture.
type ImagenFlotante = Vector -> Vector -> Vector -> Picture
type Interpretacion a = a -> ImagenFlotante

-- Escala el argumento por 0.5
mitad :: Vector -> Vector
mitad = (0.5 V.*)

-- El vector nulo
zero :: Vector
zero = (0, 0)

-- Interpretaciones de los constructores de Dibujo

--interpreta el operador de rotacion
interp_rotar :: ImagenFlotante -> ImagenFlotante
interp_rotar f d w h = f (d V.+ w) h (zero V.- w)

--interpreta el operador de espejar
interp_espejar :: ImagenFlotante -> ImagenFlotante
interp_espejar f d w h = f ( d V.+ w) (zero V.- w) h 

--interpreta el operador de rotacion 45
interp_rotar45 :: ImagenFlotante -> ImagenFlotante
interp_rotar45 f d w h = f (d V.+ (mitad (w V.+ h))) (mitad (w V.+ h)) (mitad (h V.- w))

--interpreta el operador de apilar
interp_apilar :: Float -> Float -> ImagenFlotante -> ImagenFlotante -> ImagenFlotante
interp_apilar m n f g d w h = Pictures [(f (d V.+ h') w (r V.* h)), (g d w h')]
  where
    r' = n/(m+n)
    r = m/(m+n)
    h' = r' V.* h 
--interp_apilar m n f g d w h  = Pictures[f (d V.+ (n/(m+n) V.* h)) w ((m/(m+n)) V.* h), g d w (n/(m+n) V.* h)] 

--interpreta el operador de juntar
interp_juntar :: Float -> Float -> ImagenFlotante -> ImagenFlotante -> ImagenFlotante
interp_juntar m n img1 img2 d w h = Pictures [(img1 d w' h), (img2 (d V.+ w') (r' V.* w) h)] 
  where
    r' = n/(m+n)
    r = m/(m+n)     
    w' = r V.* w   

--interpreta el operador de encimar
interp_encimar :: ImagenFlotante -> ImagenFlotante -> ImagenFlotante
interp_encimar img1 img2 d w h = Pictures [img1 d w h, img2 d w h] -- img2 quedara por "emcima" de img1

--interpreta cualquier expresion del tipo Dibujo a
--utilizar foldDib 
interp :: Interpretacion a -> Dibujo a -> ImagenFlotante
interp interpBas = foldDib interpBas interp_rotar interp_rotar45 interp_espejar interp_apilar interp_juntar interp_encimar --chequear


