# Stage 1: Build C++ shared library for GOST R 34.12-2015 encryption and decryption algorithm
FROM alpine@sha256:a8560b36e8b8210634f77d9f7f9efd7ffa463e380b75e2e74aff4511df3ef88c AS build-env

# Install build tools
RUN apk add --no-cache build-base

# Set working directory and copy source files (.h and .cpp needed for build)
WORKDIR /app
COPY src/kuznechik_crypto/ src/kuznechik_crypto/

# Build the shared library
RUN g++ -DDEBUG -fPIC -shared -static -o kuznechik.so src/kuznechik_crypto/encryption/kuznechik.cpp

# Stage 2: Build final image with Python application
FROM python@sha256:0733909561f552d8557618ee738b2a5cbf3fddfddf92c0fb261b293b90a51f12

LABEL author="Rezabungel"

# Install required Python libraries
COPY requirements.txt .
RUN pip3.10 install --no-cache-dir -r requirements.txt

# Set working directory and copy source code and configuration files
WORKDIR /app
COPY src/kuznechik_crypto/ src/kuznechik_crypto/
COPY config/kuznechik_crypto/ config/kuznechik_crypto/

# Copy the built shared library from the build stage
COPY --from=build-env /app/kuznechik.so lib/

# Remove C++ source files (.h and .cpp)
RUN find /app/src/kuznechik_crypto/ -type f \( -name "*.h" -o -name "*.cpp" \) -exec rm -f {} +

# Create a non-root user for security purposes and change the ownership of application files to this user
RUN adduser -D non-root && \
    chown -R non-root:non-root /app

# Switch to non-root user
USER non-root

# Expose the application port
EXPOSE 8000

# Set working directory and run the application
WORKDIR /app/src/kuznechik_crypto
CMD ["python3.10", "main.py"]