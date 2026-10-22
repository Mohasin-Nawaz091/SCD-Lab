import re

posts = [
    "@Ali: Phone X12 is EXCELLENT! #TechReview https://example.com/review",
    "@Sara99: Great camera, but average battery life. #Smartphone",
    "@TechWorld: Phone X12 costs $799 and Phone X13 costs $899. #PriceCheck",
    "@Bilal: I love the new PHONE X14! It has 5G support. #Innovation",
    "@Ayesha: EXCELLENT performance and GREAT design! #TechNews",
    "@MobileFan: Phone X15 is available for $999. #NewLaunch",
    "@Hamza: The camera is great, and the display is EXCELLENT! #Photography",
    "@ZaraTech: Phone X16 has 12GB RAM and costs $1099. https://example.com/phone",
    "@Usman: I love Phone X17, but its battery lasts only 8 hours. #Review",
    "@TechGuru: GREAT features at just $699! Phone X18 is impressive. #Gadgets",
    "@Mina: Phone X19 has 256GB storage and excellent performance. #Technology",
    "@Farhan: I LOVE this smartphone! Phone X20 costs $1199. #PremiumPhone",
    "@DigitalWorld: Phone X21 supports 5G and has 16GB RAM. #MobileTech",
    "@Hira: Great price, excellent camera, and amazing design! #BestPhone",
    "@AhmedTech: Phone X22 is priced at $899, while Phone X23 costs $999. #Comparison"
]

for post in posts:

    models = re.findall(
        r'\bPhone\s+(?=[A-Z]\d+\b)[A-Z]\d+\b',
        post,
        re.IGNORECASE
    )

    prices = re.findall(r'(?<=\$)\d+', post)

    hashtags = re.findall(r'(?<=#)\w+', post)

    keywords = re.findall(
        r'\b(?:excellent|great|love)\b',
        post,
        re.IGNORECASE
    )

    numbers = re.findall(r'(?<!\$)\b\d+\b', post)

    cleaned = re.sub(r'https?://\S+', '', post)

    cleaned = re.sub(r'@\w+', '', cleaned)

    cleaned = re.sub(r'\s+', ' ', cleaned).strip()

    cleaned = cleaned.lower()

    print("\nCleaned Post:", cleaned)
    print("Keywords:", keywords)
    print("Hashtags:", hashtags)
    print("Prices:", prices)
    print("Phone Models:", models)
    print("Numbers not preceded by $:", numbers) 