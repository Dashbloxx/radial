#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <string.h>

#include "discord.h"
#include "string.h"

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	string_t *string = (string_t *)userp;

	size_t _size = string->size + realsize + 1;

	string->memory = realloc(string->memory, _size);

	if(string->memory == NULL)
	{
		fprintf(stderr, "Failed to allocate %ld bytes!\r\n", _size);
		return 0;
	}

	memcpy(&(string->memory[string->size]), contents, realsize);
	string->size += realsize;
	string->memory[string->size] = 0;

	return realsize;
}

int experiments(string_t *fingerprint)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://discord.com/api/v9/experiments");

		string_t chunk;
		chunk.memory = malloc(1);
		chunk.size = 0;

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
		{
			return -1;
		}

		cJSON *json_object = cJSON_Parse(chunk.memory);
		if(json_object)
		{
			cJSON *fingerprint_json_object = cJSON_GetObjectItemCaseSensitive(json_object, "fingerprint");

			if(cJSON_IsString(fingerprint_json_object))
			{
				strcpy(fingerprint->memory, fingerprint_json_object->valuestring);
				fingerprint->size = strlen(fingerprint_json_object->valuestring);
			}
			else
			{
				cJSON_Delete(json_object);
				return -2;
			}

			cJSON_Delete(json_object);
		}
		else
		{
			return -3;
		}

		free(chunk.memory);

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return 0;
}