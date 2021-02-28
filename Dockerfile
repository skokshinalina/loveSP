FROM ubuntu:18.04
COPY . /new.sh
RUN chmod ugo+rwx new.sh
