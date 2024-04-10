FROM nvidia/cuda:12.4.1-devel-ubuntu22.04
LABEL authors="wangyw15"

WORKDIR /app
COPY ./src/main.cu ./main.cu
RUN nvcc -O3 -o main main.cu
ENTRYPOINT ["./main"]

# Build the image
# docker build -t mycuda:1.0 .
# Run the container
# docker run --rm -it --gpus all mycuda:1.0