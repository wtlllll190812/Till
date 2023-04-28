#include <unordered_map>
#include "parser.h"

// ���ȼ���
const std::unordered_map<token::token_type, parser::Precedence> PRECEDENCES = 
{
    {token::EQ, parser::Precedence::EQUALS},
    {token::NEQ, parser::Precedence::EQUALS},
    {token::LT, parser::Precedence::LESSGREATER},
    {token::GT, parser::Precedence::LESSGREATER},
    {token::LTE, parser::Precedence::LESSGREATER},
    {token::GTE, parser::Precedence::LESSGREATER},
    {token::PLUS, parser::Precedence::SUM},
    {token::MINUS, parser::Precedence::SUM},
    {token::SLASH, parser::Precedence::PRODUCT},
    {token::ASTERISK, parser::Precedence::PRODUCT},
    {token::LPAREN, parser::Precedence::CALL},
    {token::LBRACKET, parser::Precedence::INDEX},
};

parser::parser()
{
    // ע��ǰ׺��������
    _prefix_parse_funcs[token::IDENT] = std::bind(&parser::parse_identifier, this);
    _prefix_parse_funcs[token::INT] = std::bind(&parser::parse_integer_literal, this);
    _prefix_parse_funcs[token::STRING] = std::bind(&parser::parse_string_literal, this);
    _prefix_parse_funcs[token::TRUE] = std::bind(&parser::parse_boolean_literal, this);
    _prefix_parse_funcs[token::FALSE] = std::bind(&parser::parse_boolean_literal, this);
    _prefix_parse_funcs[token::FUNCTION] = std::bind(&parser::parse_function_literal, this);
    _prefix_parse_funcs[token::LPAREN] = std::bind(&parser::parse_group_expression, this);
    _prefix_parse_funcs[token::BANG] = std::bind(&parser::parse_prefix_expression, this);
    _prefix_parse_funcs[token::MINUS] = std::bind(&parser::parse_prefix_expression, this);
    _prefix_parse_funcs[token::IF] = std::bind(&parser::parse_if_expression, this);
    _prefix_parse_funcs[token::LBRACKET] = std::bind(&parser::parse_array_literal, this);
    _prefix_parse_funcs[token::LBRACE] = std::bind(&parser::parse_hash_literal, this);

    // ע����׺��������
    _infix_parse_funcs[token::PLUS] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::MINUS] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::ASTERISK] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::SLASH] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::EQ] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::NEQ] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::LT] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::GT] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::LTE] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::GTE] = std::bind(&parser::parse_infix_expression, this, std::placeholders::_1);
    // �� call ���ʽ�У����� add(1, 2 * 3)�����ǰ� ( ��������׺����������������ߵ����ȼ�
    _infix_parse_funcs[token::LPAREN] = std::bind(&parser::parse_call_expression, this, std::placeholders::_1);
    _infix_parse_funcs[token::LBRACKET] = std::bind(&parser::parse_index_expression, this, std::placeholders::_1);
}

std::unique_ptr<program> parser::parse(std::string& text)
{
	m_text = text;
	init();
	auto program = std::make_unique<class program>();
	while (m_current_token.type != token::END)
	{
		auto stmt = parse_statement();
		if (stmt)
		{
			program->add_statement(stmt.release());
		}
		next_token();
	}

	return program;
}

void parser::init()
{
	m_lexer.set_text(m_text);

	m_current_token = m_lexer.get_next_token();
	m_next_token = m_lexer.get_next_token();
}

void parser::next_token()
{
	m_current_token = m_next_token;
	m_next_token = m_lexer.get_next_token();
}

std::unique_ptr<statement> parser::parse_statement()
{
    switch (m_current_token.type)
    {
    case token::LET:
        return parse_let_statment();
    case token::RETURN:
        return parse_return_statment();
    default:
        return parse_expression_statment();
    }

    return nullptr;
}

/// <summary>
/// ��ȡһ��let�ؼ���
/// </summary>
/// <returns></returns>
std::unique_ptr<statement> parser::parse_let_statment()
{
    std::unique_ptr<let_statement> stmt(new let_statement(m_current_token));

    // �鿴��һ�� token����ȡ��
    if (m_next_token.type != token::IDENT)
    {
        return nullptr;
    }
    next_token();

    stmt->set_identifier(new identifier(m_current_token, m_current_token.value));

    // ��ʶ������һ�� token ������ = ��
    if (m_next_token.type !=token::ASSIGN)
    {
        return nullptr;
    }

    // ���� = ��
    next_token();
    next_token();

    // ���ʽ��������
    auto exp = parse_expression(Precedence::LOWEST);
    stmt->set_expression(exp.release());

    if (m_next_token.type == token::SEMICOLON)
    {
        next_token();
    }

    return stmt;
}

/// <summary>
/// ʶ��return�ؼ���
/// </summary>
std::unique_ptr<statement> parser::parse_return_statment()
{
    auto stmt = std::make_unique<return_statement>(m_current_token);
    
    //����return
    next_token();
    //���ʽ����
    auto exp = parse_expression(Precedence::LOWEST);
    stmt->set_expression(exp.release());

    if (m_next_token.type == token::SEMICOLON)
    {
		next_token();
	}

    return stmt;
}

/// <summary>
/// ʶ����ʽ
/// </summary>
std::unique_ptr<statement> parser::parse_expression_statment()
{
    auto stmt = std::make_unique<expression_statment>(m_current_token);
    
    auto expression = parse_expression(Precedence::LOWEST);
    stmt->set_expression(expression.release());

    if (m_next_token.type == token::SEMICOLON)
    {
		next_token();
	}
    return stmt;
}

/// <summary>
/// Pratt Parsing�㷨
/// </summary>
std::unique_ptr<expression> parser::parse_expression(Precedence precedence)
{
    auto prefix = _prefix_parse_funcs.find(m_current_token.type);
   

    auto left = prefix->second();

    // precedence �����������ҽ�ϵ���������� precedence �ǵ�ǰ��ߵģ���Ŀǰ��
    // �ռ����� left_exp �Ͳ��ᱻ���ݸ� infix_parse_func
    // peek_precedence �������������ϵ�����������ζ�� peek_precedence Խ��
    // ��ǰ�ռ��� left_exp Խ���ױ� peek_token �������У����������ݸ� infix_parse_func
    while (m_next_token.type!= token::SEMICOLON && precedence < peek_precedence())
    {
        auto infix = _infix_parse_funcs.find(m_next_token.type);
        if (infix == _infix_parse_funcs.end())
        {
            return left;
        }

        next_token();
        // infix_parse_func �ڲ���ݽ� token
        auto exp = infix->second(left.release());
        left.swap(exp);
    }

    return left;
}

std::vector<std::shared_ptr<identifier>> parser::parse_function_parameters()
{
    std::vector<std::shared_ptr<identifier>> idents;
    if (m_next_token.type == token::RPAREN)
    {
        next_token();
        return idents;
    }
    next_token();
    idents.emplace_back(new identifier(m_current_token, m_current_token.value));

    while (m_next_token.type==token::COMMA)
    {
        next_token(); // comma
        next_token(); // param
        idents.emplace_back(new identifier(m_current_token, m_current_token.value));
    }
    return idents;
}

std::unique_ptr<block_statement> parser::parse_block_statement()
{
    auto block = std::make_unique<block_statement>(m_current_token);
    next_token();

    while (m_current_token.type != token::RBRACE && m_current_token.type != token::END)
    {
        auto stmt = parse_statement();
        if (stmt)
        {
			block->append(stmt.release());
		}
		next_token();
    }

    if (m_current_token.type == token::END)
    {
        return nullptr;
    }

    return block;
}

parser::Precedence parser::current_precedence() const
{
    auto it = PRECEDENCES.find(m_current_token.type);
    if (it != PRECEDENCES.end())
    {
        return it->second;
    }
    return Precedence::LOWEST;
}

parser::Precedence parser::peek_precedence() const
{
    auto it = PRECEDENCES.find(m_next_token.type);
    if (it != PRECEDENCES.end())
    {
        return it->second;
    }
    return Precedence::LOWEST;
}

std::unique_ptr<expression> parser::parse_identifier()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_integer_literal()
{
    return std::unique_ptr<expression>(new integerLiteral(m_current_token));
}

std::unique_ptr<expression> parser::parse_string_literal()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_boolean_literal()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_function_literal()
{
    next_token();
    auto func = std::make_unique<function_literal>(m_current_token);

    if (m_next_token.type != token::LPAREN)
    {
        return nullptr;
    }
    next_token();

    auto params = parse_function_parameters();
    func->set_parameters(params);

    next_token();
    if (m_next_token.type != token::LBRACE)
    {
        return nullptr;
    }
    next_token();

    auto body = parse_block_statement();
    if (body == nullptr)
    {
        return nullptr;
    }
    func->set_body(body.release());
    
    return func;
}

std::unique_ptr<expression> parser::parse_array_literal()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_hash_literal()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_group_expression()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_prefix_expression()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_if_expression()
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_infix_expression(expression* left)
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_call_expression(expression* left)
{
    return std::unique_ptr<expression>();
}

std::unique_ptr<expression> parser::parse_index_expression(expression* left)
{
    return std::unique_ptr<expression>();
}
