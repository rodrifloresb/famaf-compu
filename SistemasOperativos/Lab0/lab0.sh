# Ejercicio 1 
echo -e "\e[32mEjercicio 1\e[0m\n"

grep -F 'model name' /proc/cpuinfo

# Ejercicio 2
echo -e "\e[32m\nEjercicio 2\e[0m\n"

grep -F 'model name' /proc/cpuinfo | wc -l

# Ejercicio 3
#   Dejo la linea 17 comentada para no llenar la terminal
echo -e "\e[32m\nEjercicio 3\e[0m\n"

wget https://raw.githubusercontent.com/dariomalchiodi/superhero-datascience/master/content/data/heroes.csv ; 
    awk -F ';' '{print $2}' heroes.csv | tr  'A-Z' 'a-z' | tr -d ' ' | awk 'NF {print}' > name_heroes.txt ;
        #   cat name_heroes.txt

#   rm name_heroes.txt
rm heroes.csv

# Ejercicio 4
echo -e "\e[32m\nEjercicio 4\e[0m\n"

sort -k 5nr datos/weather_cordoba.in > ord_clima.in ; echo "Dia de mayor temperatura" ; 
    head -n 1 ord_clima.in | awk '{print $1, $2 , $3}' ; sort -k 6n datos/weather_cordoba.in > ord_clima.in ; 
        echo "Dia de menor temperatura" ; head -n 1 ord_clima.in | awk '{print $1, $2, $3}'

rm ord_clima.in 

# Ejericio 5
echo -e "\e[32m\nEjercicio 5\e[0m\n"

sort -k 3nr datos/atpplayers.in > ord_players.in ; head -n 1 ord_players.in | awk '{print $1, $3}'
echo "La lista completa esta en 'ord_players.in' "

# Ejercicio 6
echo -e "\e[32m\nEjercicio 6\e[0m\n"

sort -k 2r -k 7r -k 8 datos/superliga.in > ord_superliga.in ; head -n 1 ord_superliga.in | awk '{print $1}'

# Ejercicio 7
echo -e "\e[32m\nEjercicio 7\e[0m\n"

ip link | grep -F 'link/ether'

# Ejercicio 8
echo -e "\e[32m\nEjercicio 8\e[0m\n"

mkdir serie

for i in {1..10}; do
    touch serie/fma_S01E${i}_es.srt
done

echo "paso a completado"

for i in {1..10}; do
    mv serie/fma_S01E${i}_es.srt serie/fma_S01E${i}.srt 
done

echo "paso b completado"


# Ejercicio 9
echo -e "\e[32m\nEjercicio 9\e[0m\n"

ffmpeg -i datos/video.mp4 -ss 00:00:02 -to 00:00:15 -c copy datos/output.mp4

ffmpeg -i datos/output.mp4 -i datos/Outlander_Theme.mp3 -c:v copy -c:a aac -strict experimental -b:a 192k datos/output_combinado.mp4

ffmpeg -i datos/output_combinado.mp4 -ss 00:00:00 -to 00:00:13 -c copy output_final.mp4
