//
// Created by Mason on 2022/5/10.
//

#ifndef CATEGORY_SCRIPT_COMPANY_REQUEST_API_H
#define CATEGORY_SCRIPT_COMPANY_REQUEST_API_H

#include <iostream>
#include "request_api.h"
#include "constant.h"

/**
 *
 * @param provinceName 省份名称
 * @param companyType 查询类型
 */
void requestCompanyAll(const std::string& provinceName,
                       const CompanyType& companyType);

#endif //CATEGORY_SCRIPT_COMPANY_REQUEST_API_H
