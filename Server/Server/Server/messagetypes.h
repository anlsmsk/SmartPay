#pragma once
#include "stdafx.h"



struct Payment
{
	Payment() {}

	utility::string_t cardType, transactionType;

	static Payment FromJson(const web::json::object& object) {
		Payment result;
		result.cardType = object.at(U("cardType")).as_string();
		result.transactionType = object.at(U("transactionType")).as_string();
		return result;
	}

	web::json::value AsJSON()const {

		web::json::value result = web::json::value::object();

		result[U("cardType")] = web::json::value::string(cardType);
		result[U("transactionType")] = web::json::value::string(transactionType);

		return result;
	}
};

