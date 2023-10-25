if [ ! -d mlx ]
then
	git clone https://github.com/codam-coding-college/MLX42.git mlx

fi
cd mlx
if [ ! -d build ]
then
	cmake -B build
fi
if [ -d build ]
then
	cd build
	make
else
	echo "can't run make\n"
fi 
