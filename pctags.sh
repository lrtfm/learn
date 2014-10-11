#!/bin/sh
# create tags for a project.

TAG_FLAG=_pctags

dir=`pwd`
current_dir=`pwd`

while [[ $current_dir != "/" ]]
do
    cd $current_dir
    # echo "Current_dir: $current_dir"
    if [[ -x $TAG_FLAG ]]
    then
        echo "Command found in $current_dir. Execute now..."
        ./$TAG_FLAG
        echo "Tags have done!"
        exit 0
    fi
    current_dir=`dirname $current_dir`
done

echo "Error: Command file not found!"
exit 1

# _pctags example. put it in top project dir.
# #!/bin/sh
# 
# old_pwd=`pwd`
# script_name=${old_pwd}/$0
# 
# dir_name=`dirname $script_name`
# 
# cd $dir_name
# sctags -R --c++-kinds=+p --fields=+iaS --extra=+q . 
# cd $old_pwd
