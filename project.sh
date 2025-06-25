#!/bin/sh

cmd="${1}" 
case ${cmd} in 
    # also see q-task: mount-binderfs.sh
    setup)
        sh -c 'sudo mkdir -p /dev/binderfs'
        sh -c 'sudo mount -t binder binder /dev/binderfs'
        sh -c 'sudo chmod 0666 /dev/binderfs/*'
        sh -c 'sudo chmod 0666 /dev/ashmem'
        sh -c 'sudo ln -s /dev/binderfs/* /dev/'
        ;;
    insmod)
        sh -c 'sudo insmod driver/binder/binder_linux.ko'
        sh -c 'sudo insmod driver/ashmem/ashmem_linux.ko'
        ;; 
    rmmod)
        sh -c 'sudo rmmod binder_linux'
        sh -c 'sudo rmmod ashmem_linux'
        ;; 
   *)  
      echo "`basename ${0}`:usage: [setup] | [insmod] | [rmmod]" 
      exit 1
      ;; 
esac
