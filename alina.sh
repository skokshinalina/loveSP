#!/bin/bash
echo 'Opredelenie tipa operacii'
echo 'Programma opredelyaet tip operacii nad failom: create,delete,move'
echo 'Programma vypolnena Nikolaevoy I.A. '
while true
do
printf 'kakuy operaciu vypolnit nad failom?'
read operation
case $operation in
	create)
		read -p 'Vvedite nazvanie faila' filename
		if [ -e $filename ]
		then
			echo "$filename est"
		else 
			touch $filename
			exit
		fi
		;;
		delete)
			read -p 'Vvedite nazvanie faila' filename
		       if  [ ! -e $filename ]
		       then
		echo "$filename ne naiden"
	else rm  $filename 
		exit
	fi
	;;
	move)
read -p 'Vvedite put faila' put
read -p 'Vvedite nazvanie faila' filename
read -p 'Vvedite put faila otkuda perenosim' d
if [ ! -e $filename ]
then
	echo  "$filename ne naiden"
else
    if	[ ! -f  $put ]
   then 
	       echo 'no directory'
       else 
	       cp $d $put
       fi
fi
exit
;;
*)
	echo 'Vvedeno ne to'
	;;
	esac
done

