# TyperWords

## Project description
TyperWord is a server-side application written in Go using the Gin framework. It is an HTTP server that provides the following API

The application stores the words for typing practice directly in a binary file using `embed.FS`. To add new word types, a text file containing space-separated words should be added to `internal/storage/words`, and the application will automatically read on building stage and add them to the SQLite database for further interaction.

## API
### host:port/words/(words_type)?[limit]
"Words": This endpoint takes a word type as part of endpoint path and an optional limit parameter. It retrieves the words of the specified type from an embedded binary file and returns them as a JSON response. If the limit parameter is provided, it limits the number of words returned. If the specified type is not supported, it returns an error response
### host:port/supported
"SupportedTypes": This endpoint retrieves all the supported word types from the embedded binary file and returns them as a JSON response
