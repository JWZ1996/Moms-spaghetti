class ICallable 
{
public:
	virtual void run() = 0;
};

class Command : public ICallable
{
	const std::function<void()> f;

public:

	Command();
	Command(const std::function<void()>& input);
	Command(std::function<void()>&& input);

	void run() override;
};

class IF : public ICallable
{
	std::map<const bool, std::unique_ptr<ICallable>> options;
	const bool bool_val;


public:

	IF(bool input);
	IF(IF&& input) noexcept;

	void run() override;

	IF& set(const std::function<void()>& input);
	IF&& set( IF&& input);
	IF& els(const std::function<void()>& input);
	IF&& els( IF&& input);
};