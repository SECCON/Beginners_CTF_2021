ARG GO_VERSION=1.16
ARG ALPINE_VERSION=3.12

# build-stage

FROM golang:${GO_VERSION}-alpine${ALPINE_VERSION} as build-stage

WORKDIR /app

COPY go.mod .
COPY go.sum .

RUN go mod download

COPY . .

RUN go build

# roduction-stage

FROM alpine:${ALPINE_VERSION} as production-stage

RUN addgroup appgroup && adduser --disabled-password --no-create-home appuser -G appgroup

WORKDIR /app

COPY --from=build-stage /app/bff .
COPY ./templates ./templates

RUN chown -R appuser:appgroup /app

RUN chmod +x ./bff

USER appuser

CMD ./bff
