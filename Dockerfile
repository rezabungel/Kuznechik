FROM alpine@sha256:1e42bbe2508154c9126d48c2b8a75420c3544343bf86fd041fb7527e017a4b4a

LABEL author="Rezabungel"

# Installing dependencies for building Python
RUN apk update && apk add --no-cache \
    build-base \
    libffi-dev \
    pkgconfig \
    openssl-dev \
    zlib-dev

# Downloading and building Python 3.10
WORKDIR /tmp
RUN wget https://www.python.org/ftp/python/3.10.15/Python-3.10.15.tgz && \
    tar xzvf Python-3.10.15.tgz && \
    cd Python-3.10.15/ && \
    ./configure --prefix=/opt/python3.10 --enable-optimizations && \
    make && \
    make install

# Updating the PATH environment variable to use the installed Python
ENV PATH="/opt/python3.10/bin:$PATH"

# Installing required Python libraries for the application
COPY requirements.txt .
RUN pip3.10 install -r requirements.txt

# Copying source code and configuration files
WORKDIR /app
COPY src/ src/
COPY config/ config/

# Building the shared library
RUN mkdir lib && \
    g++ -DDEBUG -fPIC -shared -o lib/kuznechik.so src/encryption/kuznechik.cpp

# Cleaning up temporary files to reduce the final image size
RUN rm -r /tmp && \
    find /app/src/ -type f \( -name "*.h" -o -name "*.cpp" \) -exec rm -f {} +

# Exposing the port for the application
EXPOSE 8000

# Running the application
WORKDIR /app/src
CMD [ "python3.10", "main.py"]