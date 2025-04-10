FROM python:3.9-slim

WORKDIR /app
COPY backend/ .
RUN pip install -r requirements.txt
RUN apt-get update && apt-get install -y g++ libssl-dev
COPY build/crypto /app/build/crypto

EXPOSE 5000
CMD ["python", "main.py"]
