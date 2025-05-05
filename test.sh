./symnmf sym tests/input_1.txt
./symnmf ddg tests/input_1.txt
./symnmf norm tests/input_1.txt
./symnmf sym tests/input_2.txt
./symnmf ddg tests/input_2.txt
./symnmf norm tests/input_2.txt
./symnmf sym tests/input_3.txt
./symnmf ddg tests/input_3.txt
./symnmf norm tests/input_3.txt
python3 symnmf.py 5 sym tests/input_1.txt 
python3 symnmf.py 5 ddg tests/input_1.txt
python3 symnmf.py 5 norm tests/input_1.txt
python3 symnmf.py 5 symnmf tests/input_1.txt
python3 analysis.py 5 tests/input_1.txt
python3 symnmf.py 4 sym tests/input_2.txt 
python3 symnmf.py 4 ddg tests/input_2.txt
python3 symnmf.py 4 norm tests/input_2.txt
python3 symnmf.py 4 symnmf tests/input_2.txt
python3 analysis.py 4 tests/input_2.txt
python3 symnmf.py 7 sym tests/input_3.txt 
python3 symnmf.py 7 ddg tests/input_3.txt
python3 symnmf.py 7 norm tests/input_3.txt
python3 symnmf.py 7 symnmf tests/input_3.txt
python3 analysis.py 7 tests/input_3.txt