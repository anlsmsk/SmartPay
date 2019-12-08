#pragma once
#include "stdafx.h"



struct Payment
{
	Payment() {}

	utility::string_t cardType, transactionType;utility::string_t id;

	static Payment FromJson(const web::json::object& object) {
		Payment result;
		result.cardType = object.at(U("cardType")).as_string();
		result.transactionType = object.at(U("transactionType")).as_string();
		result.id = object.at(U("id")).as_integer();

		return result;
	}

	web::json::value AsJSON()const {

		web::json::value result = web::json::value::object();

		result[U("cardType")] = web::json::value::string(cardType);
		result[U("transactionType")] = web::json::value::string(transactionType);
		result[U("id")] = web::json::value::string(id);

		return result;
	}
};

