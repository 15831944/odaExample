#! /bin/sh

SV_PWD="${PWD}"
SV_LD_LIBRARY_PATH=$LD_LIBRARY_PATH

cd ODADrawingsExplorer
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"

./ODADrawingsExplorer $1 $2 $3 $4 $5 $6 $7 $8 $9

export LD_LIBRARY_PATH=$SV_LD_LIBRARY_PATH
cd $SV_PWD
