#!/bin/bash
#filename find.sh
echo "made by alina skokshina"
echo -e "Поиск файлов по имени или по размеру больше назначенного
\t**************\n"
read -p "Определите поиск по имени[n] или размеру[s]: " var 
case $var in
        n) read -p "Введите имя запрашиваемого файла: " filename
                par="-type f -name $filename";;
        s) while true; do
                read -p "Используя суфикс
с - байт
k - килобайт(так же без суфикса)
М - мегабайт
G - гигабайт
Введите минимальный размер от которого
будет произведен поиск файла: " filesize
                case ${filesize##*[0-9]} in
                        [ckMG]) break;;
                        '') break;;
                        *) tput setaf 1
                                echo "ERROR! Не корректный размер файла"
                                tput sgr0
                                continue
                esac
        done
                par="-type f -size +$filesize";;
        *) tput setaf 1
                echo "ERROR! Для поиска по имени нажмите клавишу [n]
Для поиска по размеру нажмите клавишу [s]"
                tput sgr0
                exit 1
esac
read -p "Введите путь к каталогу поиска: " dirname
find $dirname $par
