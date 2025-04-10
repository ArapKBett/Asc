# Use an official Ubuntu base image with Python
FROM ubuntu:20.04

# Set working directory
WORKDIR /app

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies: Python, g++, OpenSSL, and pip
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    g++ \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy backend files
COPY . /app

# Install Python dependencies
RUN pip3 install -r requirements.txt

# Compile the C++ encryption binary
RUN g++ -o ../build/crypto crypto.cpp -lssl -lcrypto

# Expose port 5000 (Flask default)
EXPOSE 5000

# Run the Flask app
CMD ["python3", "main.py"]
