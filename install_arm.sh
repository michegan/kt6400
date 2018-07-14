#定义局部变量
INSTALL_DIR=./install

#去掉调试信息
FILES=`ls ${INSTALL_DIR}/arm/*.so`
for FILE in $FILES
do 
  arm-linux-strip ${FILE}
done