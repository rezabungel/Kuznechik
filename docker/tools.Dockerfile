# Stage 1: Build final image with Python application
FROM python@sha256:0733909561f552d8557618ee738b2a5cbf3fddfddf92c0fb261b293b90a51f12

LABEL author="Rezabungel"

# Install required Python libraries
COPY requirements.txt .
RUN pip3.10 install --no-cache-dir -r requirements.txt

# Set working directory and copy source code and configuration files
WORKDIR /app
COPY src/tools/ src/tools/
COPY config/tools/ config/tools/

# Create a non-root user for security purposes and change the ownership of application files to this user
RUN adduser -D non-root && \
    chown -R non-root:non-root /app

# Switch to non-root user
USER non-root

# Expose the application port
EXPOSE 8000

# Set working directory and run the application
WORKDIR /app/src/tools
CMD ["python3.10", "main.py"]