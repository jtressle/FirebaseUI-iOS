//
//  Copyright (c) 2017 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <UIKit/UIKit.h>

#pragma mark - Forward Declarations

@class FUIStaticContentTableViewCell;
@class FUIStaticContentTableViewContent;
@class FUIStaticContentTableViewSection;

#pragma mark - Block Type Definitions

/** @typedef FUIStaticContentTableViewCellAction
    @brief The type of block invoked when a cell is tapped.
 */
typedef void(^FUIStaticContentTableViewCellAction)(void);

#pragma mark -

/** @class FUIStaticContentTableViewManager
    @brief Generic class useful for populating a @c UITableView with static content.
    @remarks Because I keep writing the same UITableView code for every internal testing app, and
        it's getting too tedious and ugly to keep writing the same thing over and over. It makes
        our sample apps harder to maintain with all this code sprinkled around everywhere, and
        we end up cutting corners and making junky testing apps, and spending more time in the
        process.
 */
@interface FUIStaticContentTableViewManager : NSObject<UITableViewDelegate, UITableViewDataSource>

/** @property contents
    @brief The static contents of the @c UITableView.
    @remarks Setting this property will reload the @c UITableView.
 */
@property(nonatomic, strong, nullable) FUIStaticContentTableViewContent *contents;

/** @property tableView
    @brief A reference to the managed @c UITableView.
    @remarks This is needed to automatically reload the table view when the @c contents are changed.
 */
@property(nonatomic, weak, nullable) IBOutlet UITableView *tableView;

@end

#pragma mark -

/** @class FUIStaticContentTableViewContent
    @brief Represents the contents of a @c UITableView.
 */
@interface FUIStaticContentTableViewContent : NSObject

/** @property sections
    @brief The sections for the @c UITableView.
 */
@property(nonatomic, copy, readonly, nullable) NSArray<FUIStaticContentTableViewSection *> *sections;

/** @fn contentWithSections:
    @brief Convenience factory method for creating a new instance of
        @c FUIStaticContentTableViewContent.
    @param sections The sections for the @c UITableView.
 */
+ (nullable instancetype)contentWithSections:
    (nullable NSArray<FUIStaticContentTableViewSection *> *)sections;

/** @fn init
    @brief Please use initWithSections:
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/** @fn initWithSections:
    @brief Designated initializer.
    @param sections The sections in the @c UITableView.
 */
- (nullable instancetype)initWithSections:
    (nullable NSArray<FUIStaticContentTableViewSection *> *)sections;

@end

#pragma mark -

/** @class FUIStaticContentTableViewSection
    @brief Represents a section in a @c UITableView.
    @remarks Each section has a title (used for the section title in the @c UITableView) and an
        array of cells.
 */
@interface FUIStaticContentTableViewSection : NSObject

/** @property title
    @brief The title of the section in the @c UITableView.
 */
@property(nonatomic, copy, readonly, nullable) NSString *title;

/** @property cells
    @brief The cells in this section of the @c UITableView.
 */
@property(nonatomic, copy, readonly, nullable) NSArray<FUIStaticContentTableViewCell *> *cells;

/** @fn sectionWithTitle:cells:
    @brief Convenience factory method for creating a new instance of
        @c FUIStaticContentTableViewSection.
    @param title The title of the section in the @c UITableView.
    @param cells The cells in this section of the @c UITableView.
 */
+ (nullable instancetype)
    sectionWithTitle:(nullable NSString *)title
               cells:(nullable NSArray<FUIStaticContentTableViewCell *> *)cells;

/** @fn init
    @brief Please use initWithTitle:cells:
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/** @fn initWithTitle:cells:
    @brief Designated initializer.
    @param title The title of the section in the @c UITableView.
    @param cells The cells in this section of the @c UITableView.
 */
- (nullable instancetype)initWithTitle:(nullable NSString *)title
                                 cells:(nullable NSArray<FUIStaticContentTableViewCell *> *)cells;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, FUIStaticContentTableViewCellType) {
  FUIStaticContentTableViewCellTypeDefault = 0,
  FUIStaticContentTableViewCellTypeButton,
  FUIStaticContentTableViewCellTypeInput
};

/** @class FUIStaticContentTableViewCell
    @brief Represents a cell in a @c UITableView.
    @remarks Cells may be custom cells (in which you specify a @c UITableViewCell to use), or
        simple single-label cells which you supply the title text for. It does not make sense to
        specify both @c customCell and also @c title, but if a @c customCell is specified, it will
        be used instead of the @c title.
 */
@interface FUIStaticContentTableViewCell : NSObject

/** @property title
    @brief If no custom cell is being used, this is the text of the @c titleLabel of the
        @c UITableViewCell.
 */
@property(nonatomic, copy, readonly, nullable) NSString *title;

/** @property value
    @brief If no custom cell is being used, this is the text of the @c detailTextLabel of the
       @c UITableViewCell.
 */
@property(nonatomic, copy, readonly, nullable) NSString *value;

/** @property type
    @brief Style of displaying cell. Default value is @c FUIStaticContentTableViewCellTypeDefault
 */
@property(nonatomic, assign) FUIStaticContentTableViewCellType type;

/** @property action
    @brief A block which is executed when the cell is selected.
    @remarks Avoid retain cycles. Since these blocked are retained here, and your
        @c UIViewController's object graph likely retains this object, you don't want these blocks
        to retain your @c UIViewController. The easiest thing is just to create a weak reference to
        your @c UIViewController and pass it a message as the only thing the block does.
 */
@property(nonatomic, copy, readonly, nullable) FUIStaticContentTableViewCellAction action;

/** @fn cellWithTitle:
    @brief Convenience factory method for a new instance of @c FUIStaticContentTableViewCell.
    @param title The text of the @c titleLabel of the @c UITableViewCell.
 */
+ (nullable instancetype)cellWithTitle:(nullable NSString *)title;

/** @fn cellWithTitle:value:
    @brief Convenience factory method for a new instance of @c FUIStaticContentTableViewCell.
    @param title The text of the @c titleLabel of the @c UITableViewCell.
    @param value The text of the @c detailTextLabel of the @c UITableViewCell.
 */
+ (nullable instancetype)cellWithTitle:(nullable NSString *)title
                                 value:(nullable NSString *)value;

/** @fn cellWithTitle:action:
    @brief Convenience factory method for a new instance of @c FUIStaticContentTableViewCell.
    @param title The text of the @c titleLabel of the @c UITableViewCell.
    @param action A block which is executed when the cell is selected.
 */
+ (nullable instancetype)cellWithTitle:(nullable NSString *)title
                                action:(nullable FUIStaticContentTableViewCellAction)action;

/** @fn cellWithTitle:action:type:
    @brief Convenience factory method for a new instance of @c FUIStaticContentTableViewCell.
    @param title The text of the @c titleLabel of the @c UITableViewCell.
    @param action A block which is executed when the cell is selected.
    @param type Style of displaying cell.
 */
+ (nullable instancetype)cellWithTitle:(nullable NSString *)title
                                action:(nullable FUIStaticContentTableViewCellAction)action
                                  type:(FUIStaticContentTableViewCellType) type;

/** @fn cellWithTitle:value:action:
    @brief Convenience factory method for a new instance of @c FUIStaticContentTableViewCell.
    @param title The text of the @c titleLabel of the @c UITableViewCell.
    @param value The text of the @c detailTextLabel of the @c UITableViewCell.
    @param action A block which is executed when the cell is selected.
 */
+ (nullable instancetype)cellWithTitle:(nullable NSString *)title
                                 value:(nullable NSString *)value
                                action:(nullable FUIStaticContentTableViewCellAction)action;

/** @fn initWithTitle:action:type:
    @brief Designated initializer.
    @param title If no custom cell is being used, this is the text of the @c titleLabel of the
        @c UITableViewCell.
    @param title If no custom cell is being used, this is the text of the @c detailTextLabel of the
        @c UITableViewCell.
    @param action A block which is executed when the cell is selected.
    @param type Style of displaying cell.
 */
- (nullable instancetype)initWithTitle:(nullable NSString *)title
                                 value:(nullable NSString *)value
                                action:(nullable FUIStaticContentTableViewCellAction)action
                                  type:(FUIStaticContentTableViewCellType) type
    NS_DESIGNATED_INITIALIZER;

/** @fn init
    @brief Please use initWithCustomCell:title:action:
 */
- (nullable instancetype)init NS_UNAVAILABLE;

@end
