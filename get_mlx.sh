if [ ! -d mlx ]
then
	git clone https://github.com/codam-coding-college/MLX42.git mlx

fi
cd mlx
cmake -B build
if [ -d build ]
then
	cd build
	make
else
	echo "can't run make\n"
fi 
