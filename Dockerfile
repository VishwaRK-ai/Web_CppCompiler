# 1. Use ython+Linux base image
FROM python:3.10-slim

# 2. Install the C++ Compiler (g++)
RUN apt-get update && apt-get install -y g++

# 3. Set the working directory inside the server
WORKDIR /app

# 4. Copy your requirements and install them
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# 5. Copy the rest of your project files
COPY . .

# Run the app using Gunicorn on port 10000
CMD ["gunicorn", "-b", "0.0.0.0:10000", "app:app"]
