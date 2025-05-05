from setuptools import Extension, setup

module = Extension("symnmfsp", sources=['symnmfmodule.c','array_2d.c','matrix.c','python_args.c','symnmflib.c'])
setup(name='symnmfsp',
     version='1.0',
     description='Calculate symnmf from data',
     ext_modules=[module])