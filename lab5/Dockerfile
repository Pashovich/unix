FROM python:alpine

WORKDIR /usr/src/app


RUN pip install --upgrade pip

RUN pip install --no-cache-dir flask


COPY lab5.py ./

CMD [ "python", "lab5.py"]